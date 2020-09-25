cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lab2)

project(INF265 C)

find_package(BISON)

BISON_TARGET(parser lenguaje.y ${CMAKE_CURRENT_SOURCE_DIR}/parser.c
    VERBOSE REPORT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/parser.output
)

add_executable(prog
    ${BISON_parser_OUTPUTS}
)

