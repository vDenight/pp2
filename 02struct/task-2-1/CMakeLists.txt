cmake_minimum_required(VERSION 3.30)
project(task_2_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(task_2_1 main.c
		point.h
		point.c)

target_link_libraries(task_2_1 -lm)
