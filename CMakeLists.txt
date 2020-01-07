cmake_minimum_required(VERSION 3.9)

project(split-string)

set(CMAKE_CXX_STANDARD 17)

add_library(split-string INTERFACE)
target_include_directories(split-string INTERFACE include)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE split-string)
if (NOT MSVC)
  target_compile_options(example
    PRIVATE -fno-exceptions
            -Wall
            -Wsign-compare
  )
endif()

