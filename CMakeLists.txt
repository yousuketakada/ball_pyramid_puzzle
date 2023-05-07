cmake_minimum_required(VERSION 3.20)
project(ball_pyramid_puzzle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

if (MSVC)
    add_compile_options(/FC)
    add_compile_options(/utf-8)
    add_compile_options(/W4)
    add_compile_options(/permissive-)
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
