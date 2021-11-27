#include <iostream>
#include "pybind11/pybind11.h"

void say_Hello() {
    std::cout << "Hello, World!" << std::endl;
}

struct MyData {
    float x, y;

    MyData() : x(0), y(0) {}

    MyData(float x, float y) : x(x), y(y) {}

    void print() const {
        std::cout << x << ", " << y << std::endl;
    }

    virtual ~MyData() = default;
};

PYBIND11_MODULE(pybind11module, module) {
    module.doc() = "Pybind11Module";
    module.def("say_Hello", &say_Hello);
    pybind11::class_<MyData>(module, "MyData")
            .def(pybind11::init<>())
            .def(pybind11::init<float, float>(), "constructor 2", pybind11::arg("x"), pybind11::arg("y"))
            .def("print", &MyData::print)
            .def_readwrite("x", &MyData::x)
            .def_readwrite("y", &MyData::y);
}
