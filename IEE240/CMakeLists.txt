cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_FLAGS_DEBUG -g)

project(IEE240 C ASM_NASM)

set(MY_FLAGS -m32)

# use c linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})

set(my_base_dir "pc1/")

# nasm sources
set(asm_src
    integral.asm
)

# c sources
set(c_src
    main.c
)

list(TRANSFORM asm_src PREPEND ${my_base_dir})
list(TRANSFORM c_src PREPEND ${my_base_dir})

set_source_files_properties(${asm_src} PROPERTIES LANGUAGE ASM_NASM)
add_library(asm_funcs ${asm_src})
set_target_properties(asm_funcs PROPERTIES LINK_OPTIONS "${MY_FLAGS}")

# always add dummy file
file(WRITE null.c "")
add_executable(prog ${c_src} null.c)
set_target_properties(prog PROPERTIES COMPILE_OPTIONS "${MY_FLAGS}" LINK_OPTIONS "${MY_FLAGS}")
target_link_libraries(prog asm_funcs)
