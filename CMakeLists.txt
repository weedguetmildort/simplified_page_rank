cmake_minimum_required(VERSION 3.23)
project(simplified_page_rank)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(simplified_page_rank
        src/main.cpp
        src/main.h)
