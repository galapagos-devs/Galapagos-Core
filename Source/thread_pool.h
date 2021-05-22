#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <future>
#include <memory>
#include <utility>
#include <type_traits>
#include <stdexcept>

typedef std::function<void()> task_t;

class thread_pool {
private:
    std::vector<std::thread> _threads;
    std::queue<task_t> _tasks;

    std::mutex _lock;
    std::condition_variable _condition;
    bool _stop;

public:
    thread_pool();
    explicit thread_pool(size_t num_threads);
    ~thread_pool();

    template<class Func, class... Args>
    auto bind_work(Func&& func, Args&&... args)
        -> std::future<typename std::invoke_result<Func, Args...>::type>;
};

inline thread_pool::thread_pool() : thread_pool(std::thread::hardware_concurrency()) {}
inline thread_pool::thread_pool(size_t num_threads)
        : _stop{false}
{
    for(size_t i = 0; i < num_threads; i++) {
        _threads.emplace_back([this]() {
            while(true) {
                task_t task;

                {
                    std::unique_lock<std::mutex> lock(_lock);
                    _condition.wait(lock, [this] { return _stop || !_tasks.empty(); });
                    if(_stop && _tasks.empty())
                        return;

                    task = std::move(_tasks.front());
                    _tasks.pop();
                }

                task();
            }
        });
    }
}

inline thread_pool::~thread_pool() {
    {
        std::unique_lock<std::mutex> lock(_lock);
        _stop = true;
    }

    _condition.notify_all();
    for(auto& thread : _threads)
        thread.join();
}

template<class Func, class... Args>
inline auto thread_pool::bind_work(Func&& func, Args&&... args)
    -> std::future<typename std::invoke_result<Func, Args...>::type> {
    using return_type = typename std::invoke_result<Func, Args...>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
    );

    std::future<return_type> response = task->get_future();
    {
        std::unique_lock<std::mutex> lock(_lock);
        if(_stop)
            throw std::runtime_error("can't bind work on a stopped thread_pool");

        _tasks.emplace([task]() { (*task)(); });
    }

    _condition.notify_one();
    return response;
}

#endif /* _THREAD_POOL_H_ */
