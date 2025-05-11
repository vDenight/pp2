cmake_minimum_required(VERSION 3.30)
project(task_5_12 C)

set(CMAKE_C_STANDARD 11)

add_executable(task_5_12
		format_type.h
		statistics_utils.h
		statistics_utils.c
		main.c)

target_link_libraries(task_5_12 m)
