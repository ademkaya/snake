cmake_minimum_required(VERSION 3.16)
project(SNAKE C)

set(CMAKE_C_STANDARD 11)

include_directories(base/snakeApp/src)

add_executable(SNAKE
        base/snakeApp/src/doublyLinkedList.c
        base/snakeApp/src/doublyLinkedList.h
        base/snakeApp/src/print.c
        base/snakeApp/src/print.h
        base/snakeApp/src/snakeApp.c
        base/snakeApp/src/snakeSrc.c
        base/snakeApp/src/snakeSrc.h)
