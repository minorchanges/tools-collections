cmake_minimum_required(VERSION 3.22)

project(cpplab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(cpplab 
    src/HelperClass/HelperClass.cpp
    src/HelperClass/HelperClass.hpp
    src/tools/timer.h
    src/tools/random.h
    src/main.cpp
)

target_include_directories(cpplab PRIVATE 
    src/
    src/HelperClass/
    src/tools
)
