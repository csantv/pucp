cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_FLAGS_DEBUG -gdwarf)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(IEE240 C ASM_NASM)

# not required for 64 bit
#set(MY_FLAGS -no-pie)

# use c linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})

# folder where all sources are
set(BASE_DIR "./pc3/")

# nasm sources
set(ASM_SRC
    func.asm
    #hello64.s
    #geometricSerieASM.asm
)

# c sources
set(C_SRC
    mv_mult.c
    #preg2.c
)

list(TRANSFORM ASM_SRC PREPEND ${BASE_DIR})
list(TRANSFORM C_SRC PREPEND ${BASE_DIR})

set_source_files_properties(${ASM_SRC} PROPERTIES LANGUAGE ASM_NASM)
add_library(asm_funcs ${ASM_SRC})
set_target_properties(asm_funcs PROPERTIES LINK_OPTIONS "${MY_FLAGS}")

# always add dummy file
file(WRITE null.c "")
add_executable(prog ${C_SRC} null.c)
set_target_properties(prog PROPERTIES COMPILE_OPTIONS "${MY_FLAGS}" LINK_OPTIONS "${MY_FLAGS}")
target_link_libraries(prog asm_funcs m)
