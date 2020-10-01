cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/c5)

project(INF265 C)

find_package(BISON)

BISON_TARGET(parser calc7.y ${CMAKE_CURRENT_SOURCE_DIR}/parser.c
    VERBOSE REPORT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/parser.output
)

add_executable(prog
    c5/calc.c
    c5/calc.h
    #lab2-grupal/lex.c
    ${BISON_parser_OUTPUTS}
)

target_link_libraries(prog m)

