cmake_minimum_required(VERSION 3.13)
project(uulp C)

set(CMAKE_C_STANDARD 11)

add_executable(ch1_more ch1/main.c)
add_executable(who ch2/who.c ch2/utmplib.c ch2/utmplib.h)
add_executable(cp ch2/cp.c)
add_executable(ls ch3/ls.c)