cmake_minimum_required(VERSION 3.10.2)
project(string_view_lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    lib/concat.hpp
)