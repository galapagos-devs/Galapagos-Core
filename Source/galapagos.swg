%module galapagos
%{
#include "API/chromosome.h"
#include "API/creature.h"
#include "API/crossover.h"
#include "API/galapagos.h"
#include "API/galapagos_metadata.h"
#include "API/genetic_operator.h"
#include "API/mutation.h"
#include "API/population.h"
#include "API/selection_algorithm.h"
#include "API/stochastic.h"
#include "API/termination_condition.h"
%}

extern "C" population* gc_create_population(population_metadata* population_metadata);
extern "C" void gc_delete_population(population* population);

%inline %{
    class PyLogFunc {
        PyObject* py_log_func;
    public:
        PyLogFunc(const PyLogFunc& o) : py_log_func(o.py_log_func) {
            Py_XINCREF(py_log_func);
        }
        PyLogFunc(PyObject *func) : py_log_func(func) {
                Py_XINCREF(this->py_log_func);
                assert(PyCallable_Check(this->py_log_func));
        }
        ~PyLogFunc() {
            Py_XDECREF(py_log_func);
        }
        void operator()(struct log_entry* entry) {
            if (!py_log_func || Py_None == py_log_func || !PyCallable_Check(py_log_func))
                return;

            PyObject *args;
            Py_XINCREF(args);
            args = SWIG_Python_NewPointerObj(NULL, entry, SWIGTYPE_p_log_entry, 0);

            PyObject *result = PyObject_Call(py_log_func, args, 0);
            Py_DECREF(args);
            Py_XDECREF(result);
        }
    };
%}


%typemap(in) log_func_t %{
    if(PyCallable_Check($input)) {
        $1 = (log_func_t) *PyLogFunc($input);
    }
%}

%include "API/galapagos_metadata.h"
%include "API/population.h"
%include "API/creature.h"
%include "API/chromosome.h"
