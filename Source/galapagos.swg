%module(directors="1") galapagos
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

%include <stdint.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>

%template(ChromosomeMetadata) std::vector<const chromosome_metadata_t*>;
%template(CrossoverMetadata) std::vector<const crossover_metadata_t*>;
%template(MutationMetadata) std::vector<const mutation_metadata_t*>;
%template(SelectionAlgorithmMetadata) std::vector<const selection_algorithm_metadata_t*>;
%template(TerminationConditionMetadata) std::vector<const termination_condition_metadata_t*>;

extern "C" population* gc_create_population(population_metadata* population_metadata);
extern "C" void gc_delete_population(population* population);
extern "C" void gc_initialize();
extern "C" void gc_reset();

// region functor Python wrappings

/* FIXME: Both of these functors are an extremal naive implementation that was ripped from stackoverflow.
          Knowledge of Python/C API is needed to make this more mature. */

/* FIXME: The `typemap`\ s for these functors are abysmal.
          They lack any sort of error checking or validation and are extremal limited. */

// TODO: Investigate performance cost of type-mapping & invoking fitness/log funcs as python objects.

%ignore PyLogFunc;
%inline %{
class PyLogFunc {
    PyObject* py_log_func;
public:
    PyLogFunc(const PyLogFunc& o) : py_log_func(o.py_log_func) {
        Py_XINCREF(py_log_func);
    }
    PyLogFunc(PyObject* func) : py_log_func(func) {
            Py_XINCREF(this->py_log_func);
            assert(PyCallable_Check(this->py_log_func));
    }
    ~PyLogFunc() {
        Py_XDECREF(py_log_func);
    }
    void operator()(log_entry_t entry) {
        if (!py_log_func || Py_None == py_log_func || !PyCallable_Check(py_log_func))
            return;

        PyObject* args;
        Py_XINCREF(args);
        args = SWIG_Python_NewPointerObj(NULL, &entry, SWIGTYPE_p_log_entry, 0);  // This is abusing SWIG internal API

        PyObject* result = PyObject_Call(py_log_func, args, 0);
        Py_DECREF(args);
        Py_XDECREF(result);
    }
};
%}

%typemap(in) log_func_t %{
    if(PyCallable_Check($input)) {
        PyLogFunc py_log_func($input);
        $1 = py_log_func;
    }
%}

%ignore PyFitnessFunc;
%inline %{
class PyFitnessFunc {
    PyObject* py_fitness_func;
public:
    PyFitnessFunc(const PyFitnessFunc& o) : py_fitness_func(o.py_fitness_func) {
        Py_XINCREF(py_fitness_func);
    }
    PyFitnessFunc(PyObject* func) : py_fitness_func(func) {
            Py_XINCREF(this->py_fitness_func);
            assert(PyCallable_Check(this->py_fitness_func));
    }
    ~PyFitnessFunc() {
        Py_XDECREF(py_fitness_func);
    }
    double operator()(creature* creature) {
        if (!py_fitness_func || Py_None == py_fitness_func || !PyCallable_Check(py_fitness_func))
            return -1.0;

        PyObject* args;
        Py_XINCREF(args);
        args = SWIG_Python_NewPointerObj(NULL, &creature, SWIGTYPE_p_creature, 0);  // This is abusing SWIG internal API

        PyObject* result = PyObject_Call(py_fitness_func, args, 0);
        Py_DECREF(args);
        Py_XDECREF(result);

        // This is a limited form of python->C type conversion. `PyFloat_AsDouble` offers some error checking.
        return PyFloat_AS_DOUBLE(result);
    }
};
%}

%typemap(in) fitness_func_t %{
    if(PyCallable_Check($input)) {
        PyFitnessFunc py_fitness_func($input);
        $1 = py_fitness_func;
    }
%}

// endregion

%ignore genetic_operator_metadata;  // Might not need `genetic_operator_metadata` so we could possible ignore it
%include "API/galapagos_metadata.h"

//%feature("director") crossover_metadata;

%include "API/population.h"
%include "API/creature.h"
%include "API/chromosome.h"
