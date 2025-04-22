cmake_minimum_required(VERSION 3.30)
project(task_4_10 C)

set(CMAKE_C_STANDARD 11)

add_executable(task_4_10 main.c
        circular_buffer.h
        circular_buffer.c)
