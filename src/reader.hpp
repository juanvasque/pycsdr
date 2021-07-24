#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <csdr/reader.hpp>

struct Reader: PyObject {
    Csdr::UntypedReader* reader;
    PyObject* readerFormat;
};

extern PyType_Spec ReaderSpec;