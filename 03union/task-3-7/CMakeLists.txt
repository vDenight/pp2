cmake_minimum_required(VERSION 3.31)
project(task_3_7 C)

set(CMAKE_C_STANDARD 11)

add_executable(task_3_7 main.c
        double_to_char.h
        double_to_char.c
        read_line.h
        read_line.c)
