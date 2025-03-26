cmake_minimum_required(VERSION 3.30)
project(task1 C)

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_SOURCE_DIR}/text.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/empty.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/text2.txt DESTINATION ${CMAKE_BINARY_DIR})

add_executable(task1 main.c)
