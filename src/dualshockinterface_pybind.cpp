#include <pybind11/pybind11.h>
#include "dualshockinterface.h"

namespace py = pybind11;

PYBIND11_MODULE(libdualshockinterface, m) {
    // Wrap DualShockInterface class
    py::class_<DualShockInterface>(m, "DualShockInterface")
        .def(py::init<const std::string&>())
        .def("start_listening", &DualShockInterface::startListening)
        .def("stop", &DualShockInterface::stop);

    // Add other bindings as needed...
}