cmake_minimum_required(VERSION 3.9)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler main.cpp scanner.h scanner.cpp parser.cpp parser.h error.h error.cpp semantic.h semantic.cpp generate.cpp generate.h)