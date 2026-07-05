cmake_minimum_required(VERSION 3.22)

project(qtthreadmodnew LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)

add_executable(${PROJECT_NAME} ${sourceFiles})
target_include_directories(${PROJECT_NAME} PRIVATE ${includeDirs})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

if (MSVC)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "windeployqt" "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Deploying Qt..."
    )
endif()
