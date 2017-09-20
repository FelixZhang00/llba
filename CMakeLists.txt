cmake_minimum_required(VERSION 3.8)
project(llba)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ch02/elfparser.c)

add_executable(llba ${SOURCE_FILES})