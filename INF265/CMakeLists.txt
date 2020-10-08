cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(INF265 C)

find_package(BISON)

BISON_TARGET(parser
    lab4-grupal/obsidian.y
    ${CMAKE_CURRENT_SOURCE_DIR}/out/parser.c
    DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/out/parser.h
    VERBOSE REPORT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/out/parser.output
)

include_directories(out)

add_executable(prog
    #c6/lex.c
    ${BISON_parser_OUTPUTS}
)

target_link_libraries(prog m)

