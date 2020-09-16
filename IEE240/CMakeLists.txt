cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_FLAGS_DEBUG -g)

project(hello C ASM_NASM)

set(MY_FLAGS -no-pie -m32)

# use c linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})

# nasm sources
set(ASM_SRC
    fuerte2.s
    #fuerte.s
    #scanf.s
    #hello.s
    #asd1.s
)

set_source_files_properties(${ASM_SRC} PROPERTIES LANGUAGE ASM_NASM)
add_library(asm_funcs ${ASM_SRC})
target_link_options(asm_funcs PRIVATE ${MY_FLAGS})

# C sources
set(C_SRC
    fuerte2.c
)

# always add dummy file
file(WRITE null.c "")
add_executable(hello ${C_SRC} null.c)

set_target_properties(hello PROPERTIES COMPILE_OPTIONS "${MY_FLAGS}" LINK_OPTIONS "${MY_FLAGS}")
target_link_libraries(hello asm_funcs)
