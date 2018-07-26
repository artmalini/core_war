cmake_minimum_required(VERSION 3.9)
project(CoreWar_VM)

set(CMAKE_C_STANDARD 99)

include_directories(includes/)
include_directories(libft/includes/)

set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Werror ")

set(SOURCE_FILES
		virtual_machine/vm_add.c
		virtual_machine/vm_aff.c
		virtual_machine/vm_and.c
#		virtual_machine/vm_and1.c
		virtual_machine/vm_arena.c
		virtual_machine/vm_cmd.c
		virtual_machine/vm_cycles.c
		virtual_machine/vm_debug.c
		virtual_machine/vm_errors.c
		virtual_machine/vm_fork.c
		virtual_machine/vm_free_and_init.c
		virtual_machine/vm_ld.c
		virtual_machine/vm_ldi.c
		virtual_machine/vm_lfork.c
		virtual_machine/vm_live.c
		virtual_machine/vm_lld.c
		virtual_machine/vm_lldi.c
		virtual_machine/vm_load.c
		virtual_machine/vm_lst.c
		virtual_machine/vm_main.c
		virtual_machine/vm_mng_bit1.c
		virtual_machine/vm_mng_bit2.c
		virtual_machine/vm_mng_func.c
		virtual_machine/vm_ncurses.c
		virtual_machine/vm_op.c
		virtual_machine/vm_or.c
		virtual_machine/vm_params.c
		virtual_machine/vm_print.c
		virtual_machine/vm_parse_check.c
		virtual_machine/vm_st.c
		virtual_machine/vm_steps.c
		virtual_machine/vm_sti.c
		virtual_machine/vm_sub.c
		virtual_machine/vm_xor.c
		virtual_machine/vm_zjmp.c
		virtual_machine/vm_ft_other.c virtual_machine/vm_parse_read.c)

add_executable(CoreWar_VM ${SOURCE_FILES})

target_link_libraries(CoreWar_VM ${LIBFT} -lncurses)
