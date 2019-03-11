cmake_minimum_required(VERSION 3.10)
project(basicm)

add_library(basicm SHARED basicm.cc)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(basicm ${PYTHON_LIBRARIES})

set_target_properties(
    basicm
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME "basicm"
        LINKER_LANGUAGE C
)