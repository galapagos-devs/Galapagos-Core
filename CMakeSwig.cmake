# Python only currently

set(SWIG_EXECUTABLE "C:/Program Files (x86)/swigwin-4.0.1/swig")
set(SWIG_SOURCE_FILE_EXTENSIONS ".swg")

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
include_directories(Source)

set(CMAKE_SWIG_FLAGS "-c++")

find_package(Python
        REQUIRED
        COMPONENTS Interpreter Development)

file(WRITE python_info.txt
        VERSION\ =\ ${Python_VERSION}\n
        PATH\ =\ ${Python_EXECUTABLE})

include_directories(${Python_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})