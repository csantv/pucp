cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_FLAGS_DEBUG -g)

project(hello C ASM_NASM)

set(MY_FLAGS -no-pie -m32)

# use c linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})

set(my_base_dir "l1/pregunta2/")

# nasm sources
set(asm_src
    imhist.asm
    #myGCD.s
    #fuerte2.s
    #fuerte.s
    #scanf.s
    #hello.s
    #asd1.s
)

list(TRANSFORM asm_src PREPEND ${my_base_dir})

set_source_files_properties(${asm_src} PROPERTIES LANGUAGE ASM_NASM)
add_library(asm_funcs ${asm_src})
set_target_properties(asm_funcs PROPERTIES LINK_OPTIONS "${MY_FLAGS}")

# c sources
set(c_src
    readimglib.h
    testImhist.c
    #fuerte2.c
)
list(TRANSFORM c_src PREPEND ${my_base_dir})

# always add dummy file
file(WRITE null.c "")
add_executable(hello ${c_src} null.c)

set_target_properties(hello PROPERTIES COMPILE_OPTIONS "${MY_FLAGS}" LINK_OPTIONS "${MY_FLAGS}")
target_link_libraries(hello asm_funcs)
