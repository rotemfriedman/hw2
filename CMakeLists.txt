cmake_minimum_required(VERSION 3.9)
project(wet2 C)

set(CMAKE_C_STANDARD 99)

add_executable(wet2 main.c driver.c driver.h season.h team.h)