cmake_minimum_required(VERSION 3.30)
project(task_2_20 C)

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_SOURCE_DIR}/2420test1.bin DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/2420test2.bin DESTINATION ${CMAKE_BINARY_DIR})

add_executable(task_2_20 main.c)
