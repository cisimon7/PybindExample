cmake_minimum_required(VERSION 3.20)
project(PybindExample)

set(CMAKE_CXX_STANDARD 23)

set(App_Source ${PROJECT_SOURCE_DIR}/src/app)
set(PyModule ${PROJECT_SOURCE_DIR}/src/PyModule)
set(Dependencies ${PROJECT_SOURCE_DIR}/dependencies)

#Pybind11
add_subdirectory(${Dependencies}/pybind11-master)
add_subdirectory(${Dependencies}/eigen-3.4.0)

#Module created to be imported into python
pybind11_add_module(
        example_module
        ${PyModule}/cpp/module.cpp
)
pybind11_add_module(
        Algebra
        ${PyModule}/cpp/ExampleB.cpp
)
pybind11_add_module(
        Geometry
        ${PyModule}/cpp/Geometry.cpp
)

#Location of where to output binaries for modules_dir
set_target_properties(example_module PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PyModule}/bindings)
set_target_properties(Algebra PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PyModule}/bindings)
set_target_properties(Geometry PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PyModule}/bindings)

target_include_directories(
        example_module
        PUBLIC ${PyModule}/cpp
)

target_include_directories(
        Algebra
        PUBLIC ${PyModule}/cpp
        PRIVATE ${Dependencies}/eigen-3.4.0
)

target_include_directories(
        Geometry
        PUBLIC ${PyModule}/cpp
        PRIVATE ${Dependencies}/eigen-3.4.0
)

add_executable(PybindExample ${App_Source}/main.cpp)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE ${App_Source}
        PRIVATE ${PyModule}/cpp
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE pybind11::embed
)

#target_compile_features(modules_dir PUBLIC cxx_std_20)
#set_target_properties(modules_dir PROPERTIES SUFFIX ".so")
#DCMAKE_OSX_ARCHITECTURES=arm64;x86_64
