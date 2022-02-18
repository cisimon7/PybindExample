#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

void say_Hello() {
    std::cout << "Hello, World!" << std::endl;
}

int add(int i = 1, int j = 2) {
    return i + j;
}

struct MyData {
private:
    float seed;

public:
    float x, y;

    MyData() : x(0), y(0) { seed = (this->x + this->y); }

    MyData(float x, float y) : x(x), y(y) { seed = (this->x + this->y); }

    void print() const {
        std::cout << x << ", " << y << std::endl;
    }

    void setSeed(const float seed) {
        std::cout << "setting seed" << std::endl;
        this->seed = seed;
    }

    float getSeed() const {
        std::cout << "getting seed" << std::endl;
        return this->seed;
    }

    virtual ~MyData() = default;
};

PYBIND11_MODULE(example_module, module) {
    module.doc() = "Pybind11Module";

    module.attr("the_answer") = 42;

    module.def("say_Hello", &say_Hello);

    module.def("add", &add, "A function which adds two numbers",
               py::arg("i") = 1, py::arg("j") = 2);

    /* Note that there is a small runtime cost for a class with dynamic attributes. */
    py::class_<MyData>(module, "MyData", py::dynamic_attr())
            .def(py::init<>())
            .def(py::init<float, float>(), "constructor 2", py::arg("x") = 3, py::arg("y"))
            .def("print", &MyData::print)
            .def_readwrite("x", &MyData::x)
            .def_readwrite("y", &MyData::y)
            .def_property("seed", &MyData::getSeed, &MyData::setSeed)
            .def("__repr__",
                 [](const MyData &data) {
                     return "MyData(" + std::to_string(data.x) + ", " + std::to_string(data.y) + ")";
                 }
            );
}
