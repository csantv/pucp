cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_FLAGS_DEBUG -gdwarf)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(IEE240 C ASM_NASM)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)
# pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# use c linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})

# nasm sources
set(ASM_SRC
	#lab1-simd/pregunta2/imhist.asm
	lab4/codes/effectASM.asm
	lab4/codes/effectSIMD.asm
	#lab2-simd/pregunta2/geometricSerieASM.asm
	#ex1/calc_asm.asm
	#ex1-sim/taylor_sin.s
)

# c sources
set(C_SRC
	#lab1-simd/pregunta2/testImhist.c
	#lab1-simd/pregunta2/readimglib.h
	#lab2-simd/pregunta2/preg2.c
	lab4/codes/preg.c
	lab4/codes/readimglib.h
	#wea.c
	#ex1/pregunta3.c
	#ex1-sim/taylor_sin.c
    #preg2.c
)

set_source_files_properties(${ASM_SRC} PROPERTIES LANGUAGE ASM_NASM)

# always add dummy file to targets
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/null.c "")
add_executable(prog ${C_SRC} ${CMAKE_CURRENT_BINARY_DIR}/null.c)
add_executable(threadtesttool threadtesttool.c)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/null.asm "")
add_library(asm_funcs ${ASM_SRC} ${CMAKE_CURRENT_BINARY_DIR}/null.asm)

find_library(gc gc)
target_link_libraries(prog asm_funcs m gc)
target_link_libraries(threadtesttool Threads::Threads)
