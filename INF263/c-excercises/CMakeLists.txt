cmake_minimum_required(VERSION 3.16)
project(excercises C)

set(CMAKE_C_STANDARD 99)

add_executable(excercises e2/20-1/20171878_P2.c)

target_link_libraries(excercises gc)