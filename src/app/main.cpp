#include <iostream>
#include "pybind11/embed.h"

namespace py = pybind11;

static int COUNTER = 0;

void set_counter(int count) {
    COUNTER = count;
}

void say_something() {
    std::cout << "Hello Something" << std::endl;
}

/* [embedded_module] name of package to be imported to use the defined functions within.
 * [module] is the interface for creating bindings. */
PYBIND11_EMBEDDED_MODULE(embedded_module, module) {
    module.doc() = "Embedded Module"; /* Module Doc string */
    module.def("say_something", &say_something);
    module.def("set_counter", &set_counter);
}

int main() {

    pybind11::scoped_interpreter guard {

    };

    py::exec("print('Hello World!')");
    py::exec("import embedded_module\nembedded_module.say_something()");
    py::exec("embedded_module.set_counter(10)");

    std::cout << COUNTER << std::endl;

    auto sys = py::module::import("sys");
    auto os = py::module::import("os");
    py::print(sys.attr("path"));
    py::print(os.attr("path").attr("realpath")("__file__"));
    py::print(sys.attr("argv"));

    {
        auto hello_module = py::module_::import("src.app.from_python");
        auto magic_function = hello_module.attr("magic");

        magic_function("Hello");
    }

    printf("end\n");

}
