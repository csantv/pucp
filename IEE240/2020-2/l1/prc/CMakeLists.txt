cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_FLAGS_DEBUG -g)

project(hello C ASM_NASM)

# use c linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})

# source files
set(ASM_SRC
    fuerte.s
    #scanf.s
    #hello.s
    #asd1.s
)

set_source_files_properties(${ASM_SRC} PROPERTIES LANGUAGE ASM_NASM)

add_executable(hello ${ASM_SRC})
target_link_options(hello PRIVATE -no-pie -m32)
