#include <windows.h>
#include <cmath>

#include <Python.h>

// watch yout python is x86 or x64
#pragma comment(lib, "python3.lib")
#pragma comment(lib, "python37.lib")

double sinh_impl(double x);
double cosh_impl(double x);
double tanh_impl(double x);

// Python interface port
PyObject* tanh_impl(PyObject*, PyObject* o) {
	double x = PyFloat_AsDouble(o);
	return PyFloat_FromDouble(tanh_impl(x));
}

// define the exposed functions list in current module
static PyMethodDef pyCExt_functions[] = {

	// The first property is the name to python, the second is the C++ 
	// function name that contains the implementation.
	{"fast_tanh", (PyCFunction)tanh_impl, METH_O, nullptr},

	// terminate the array with an object containing nulls
	{nullptr, nullptr, 0, nullptr}
};

// define the module name and binding the functions list
static PyModuleDef pyCExt = {
	PyModuleDef_HEAD_INIT,
	"pycext",	// module name to use in python 'import' statement
	"python c extension ", // module description
	0,
	pyCExt_functions
};

// define the output function for dll module
PyMODINIT_FUNC PyInit_PyCExt() {
	return PyModule_Create(&pyCExt);
}