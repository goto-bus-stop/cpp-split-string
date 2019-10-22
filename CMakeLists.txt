cmake_minimum_required(VERSION 3.9)

project(split-string)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

if(NOT MSVC)
  add_compile_options(-fno-exceptions)
  add_definitions(-Wall -Wsign-compare)
endif()

add_executable(example example.cpp)
