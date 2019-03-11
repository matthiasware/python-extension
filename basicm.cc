#include <Python.h>
#include <iostream>

int cfib(int n)
{
    if(n < 2)
        return n;
    else
        return cfib(n - 1) + cfib(n - 2);
}

static PyObject* fib(PyObject* self, PyObject* args)
{
    int n;
    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    return Py_BuildValue("i", cfib(n));
}

static PyObject* version(PyObject* self)
{
    return Py_BuildValue("s", "Version 1.0");
}

// This is the definition of a method
static PyObject* division(PyObject *self, PyObject *args) {
    std::cout << "BLA" << std::endl;
    long dividend, divisor;
    if (!PyArg_ParseTuple(args, "ll", &dividend, &divisor)) {
        return NULL;
    }
    if (0 == divisor) {
        PyErr_Format(PyExc_ZeroDivisionError, "Dividing %d by zero!", dividend);
        return NULL;
    }
    return PyLong_FromLong(dividend / divisor);
}

// Exported methods are collected in a table
PyMethodDef method_table[] = {
    {"division", (PyCFunction) division, METH_VARARGS, "Method docstring"},
    {"fib", (PyCFunction) fib, METH_VARARGS, "Calculates fibonacci numbers"},
    {"version", (PyCFunction) version, METH_NOARGS, "returns version"},
    {NULL, NULL, 0, NULL} // Sentinel value ending the table
};

// A struct contains the definition of a module
PyModuleDef basicm_module = {
    PyModuleDef_HEAD_INIT,
    "basicm", // Module name
    "This is the module docstring",
    -1,   // Optional size of the module state memory
    method_table,
    NULL, // Optional slot definitions
    NULL, // Optional traversal function
    NULL, // Optional clear function
    NULL  // Optional module deallocation function
};

// The module init function
PyMODINIT_FUNC PyInit_basicm(void) {
    return PyModule_Create(&basicm_module);
}
