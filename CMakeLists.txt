cmake_minimum_required(VERSION 3.9)
project(CoreWar_VM)

set(CMAKE_C_STANDARD 99)

include_directories(includes)
include_directories(libft/includes)

set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( CoreWar_VM ${CURSES_LIBRARIES} )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Werror ")

set(SOURCE_FILES
		virtual_machine/op.c
		virtual_machine/vm_load.c
		virtual_machine/vm_main.c
		virtual_machine/vm_params.c
		virtual_machine/vm_read.c virtual_machine/vm_ncurses.c virtual_machine/vm_errors.c virtual_machine/vm_print.c
		virtual_machine/vm_sti.c
		virtual_machine/vm_and.c
		virtual_machine/vm_live.c
		virtual_machine/vm_zjmp.c
		virtual_machine/vm_ld.c
		virtual_machine/vm_st.c
		virtual_machine/vm_add.c
		virtual_machine/vm_sub.c
		virtual_machine/vm_ldi.c
		virtual_machine/vm_fork.c )

add_executable(CoreWar_VM ${SOURCE_FILES})

target_link_libraries(CoreWar_VM ${LIBFT})
