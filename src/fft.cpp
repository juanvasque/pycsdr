#include "fft.hpp"
#include "types.hpp"

#include <csdr/fft.hpp>
#include <csdr/window.hpp>

static int Fft_init(Fft* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "size", (char*) "every_n_samples", NULL};

    uint16_t fftSize = 0;
    uint16_t everyNSamples = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "HH", kwlist, &fftSize, &everyNSamples)) {
        return -1;
    }

    // TODO make window available as an argument
    auto window = new Csdr::HammingWindow();
    self->setModule(new Csdr::Fft(fftSize, everyNSamples, window));
    delete window;

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
    self->outputFormat = FORMAT_COMPLEX_FLOAT;

    return 0;
}

static PyObject* Fft_setEveryNSamples(Fft* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {(char*) "every_n_samples", NULL};

    uint16_t everyNSamples = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "H", kwlist, &everyNSamples)) {
        return NULL;
    }

    dynamic_cast<Csdr::Fft*>(self->module)->setEveryNSamples(everyNSamples);

    Py_RETURN_NONE;
}

static PyMethodDef Fft_methods[] = {
    {"setEveryNSamples", (PyCFunction) Fft_setEveryNSamples, METH_VARARGS | METH_KEYWORDS,
     "set repetition interval in samples"
    },
    {NULL}  /* Sentinel */
};

static PyType_Slot FftSlots[] = {
    {Py_tp_init, (void*) Fft_init},
    {Py_tp_methods, Fft_methods},
    {0, 0}
};

PyType_Spec FftSpec = {
    "pycsdr.modules.Fft",
    sizeof(Fft),
    0,
    Py_TPFLAGS_DEFAULT,
    FftSlots
};
