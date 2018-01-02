#include <Python.h>
#include <stdio.h>

static inline uint64_t _rdtsc()
{
        unsigned long _hi, _lo;
        asm volatile("rdtscp" : "=a"(_lo), "=d"(_hi));
        uint64_t val = _hi << 32 | _lo;
        return val;
}

static PyObject *
py_rdtsc(PyObject *self, PyObject *args)
{
        (void)self;
        (void)args;
        uint64_t val = _rdtsc();
        PyObject *result = Py_BuildValue("k", val);
        return result;
}

static PyMethodDef rdtsc_methods[] = {
        {"rdtsc", py_rdtsc,  METH_VARARGS, "rdtsc"},
        {0,0,0,0},     /* sentinel */
};

PyDoc_STRVAR(rdtsc_doc_module,
             "Python time measurement libraray.\n");

static struct PyModuleDef rdtsc_module = {
        PyModuleDef_HEAD_INIT,
        "rdtsc",
        rdtsc_doc_module,
        -1,
        rdtsc_methods,
        NULL,
        NULL,
        NULL,
        NULL
};

PyMODINIT_FUNC
PyInit_rdtsc(void)
{
        PyObject *m;
        m = PyModule_Create(&rdtsc_module);
        if(m == NULL) {
                return NULL;
        }
        Py_INCREF(PyExc_OSError);
        PyModule_AddObject(m, "error", PyExc_OSError);
        return m;
}

