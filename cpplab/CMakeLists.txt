cmake_minimum_required(VERSION 3.22)

project(cpplab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(sourceFiles
    src/HelperClass/HelperClass.cpp
    src/HelperClass/HelperClass.hpp
    src/tools/timer.h
    src/tools/random.h
    src/main.cpp
)

set(includeDirs
    src/
    src/HelperClass/
    src/tools
)

add_executable(cpplab ${sourceFiles})
target_include_directories(cpplab PRIVATE ${includeDirs})
