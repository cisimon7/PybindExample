cmake_minimum_required(VERSION 3.20)
project(PybindExample)

set(CMAKE_CXX_STANDARD 23)

set(App_Source ${PROJECT_SOURCE_DIR}/src/app)
set(Module_Source ${PROJECT_SOURCE_DIR}/src/module)
set(Dependencies ${PROJECT_SOURCE_DIR}/dependencies)

#Pybind11
add_subdirectory(${Dependencies}/pybind11)

#Module
pybind11_add_module(
    pybind11module
    ${Module_Source}/module.cpp
)

target_include_directories(
    pybind11module
    PRIVATE ${Module_Source}
)

add_executable(PybindExample ${App_Source}/main.cpp)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${App_Source}
    PRIVATE ${Module_Source}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE pybind11::embed
)
