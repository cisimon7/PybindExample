#include <iostream>
#include "pybind11/embed.h"

static int COUNTER = 0;

void set_counter(int count) {
    COUNTER = count;
}

void say_something() {
    std::cout << "Hello Something" << std::endl;
}

PYBIND11_EMBEDDED_MODULE(embedded_module, module) {
    module.doc() = "Embedded Module";
    module.def("say_something", &say_something);
    module.def("set_counter", &set_counter);
}

int main() {

    pybind11::scoped_interpreter guard {

    };

    pybind11::exec("print('Hello World!')");
    pybind11::exec("import embedded_module\nembedded_module.say_something()");
    pybind11::exec("embedded_module.set_counter(10)");

    std::cout << COUNTER << std::endl;

    auto sys = pybind11::module::import("sys");
    pybind11::print(sys.attr("path"));

    {
        auto hello_module = pybind11::module::import("from_python.py");
        auto magic_function = hello_module.attr("magic");

        magic_function("Hello from Magic Function");
    };

    printf("end\n");

}
