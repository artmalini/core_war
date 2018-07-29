cmake_minimum_required(VERSION 3.9)
project(Clion_asm)

set(CMAKE_C_STANDARD 99)

include_directories(includes/)
include_directories(libft/includes/)

set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Werror ")

set(SOURCE_FILES
		assembler/asm_check.c
		assembler/asm_check_args.c
		assembler/asm_cmd.c
		assembler/asm_create_cor.c
		assembler/asm_create_cor_fpos_opc.c
		assembler/asm_create_cor_instr.c
		assembler/asm_errors.c
		assembler/asm_free_struct.c
		assembler/asm_label.c
		assembler/asm_name_cmt_valid.c
		assembler/asm_parse_line.c
		assembler/asm_parse_main.c
		assembler/asm_recalc_cmd_links.c
		assembler/asm_valid_main.c
		assembler/asm_main.c
		assembler/asm_print.c
		assembler/asm_init_and_free.c
		assembler/asm_op.c)

add_executable(Clion_asm ${SOURCE_FILES})

target_link_libraries(Clion_asm ${LIBFT})
