cmake_minimum_required(VERSION 3.30)
project(task_3_10 C)

set(CMAKE_C_STANDARD 11)

set(
        SOURCE_FILES
        figure.h
        figure.c
        main.c
)

add_executable(untitled ${SOURCE_FILES})
