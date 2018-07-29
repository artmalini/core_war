# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvertohr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/06 11:03:53 by tvertohr          #+#    #+#              #
#    Updated: 2018/06/06 11:03:55 by tvertohr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../corewar
FLAGS		= -Wall -Wextra -Werror
CC			= gcc
#LD			= -lncurses

HEADERS		= ../includes
HEADERS_L	= ../libft/includes
LIBFT		= -L ../libft -lft -lcurses
LIBFT_PATH	= ../libft

SRCS_VM	=	vm_errors.c \
			vm_load.c \
			vm_main.c \
			vm_n.c \
			vm_n_logo.c \
			vm_n_heart_win.c \
			vm_n_draw_win.c \
			vm_params.c \
			vm_print.c \
			vm_read.c \
			op.c \
			vm_m_init.c \
			vm_m_free.c \
			vm_m_cmd_triger.c \
			vm_mng_func.c \
			vm_mng_bit1.c \
			vm_mng_bit2.c \
			vm_sti_mng.c \
			vm_sti.c \
			vm_and.c \
			vm_or.c \
			vm_xor.c \
			vm_live.c \
			vm_zjmp.c \
			vm_ld.c \
			vm_st.c \
			vm_add.c \
			vm_sub.c \
			vm_ldi.c \
			vm_fork.c \
			vm_lld.c \
			vm_lldi.c \
			vm_lfork.c \
			vm_aff.c \

OBJS_VM	=   $(SRCS_VM:.c=.o)

RED			= \033[31m
GREEN		= \033[32m
CYAN		= \033[36m
GREY		= \033[37m

all: $(NAME)

$(NAME): $(OBJS_VM)
	@$(CC) $(OBJS_VM) $(FLAGS) -I $(HEADERS) -I $(HEADERS_L) $(LIBFT) -o $@
	@echo "\033[0;32m ----> Created (corewar)"

$(OBJS_VM): %.o: %.c
	@$(CC) -c $(FLAGS) -I $(HEADERS) -I $(HEADERS_L) $< -o $@
	@echo "\033[0;36m ----> Created object files (corewar)"

clean:
	@rm -f $(OBJS_VM)
	@echo "\033[0;31m ----> Delete object files [corewar]"

fclean:	clean
	@rm -f $(NAME)
	@echo "\033[0;31m ----> Delete [corewar] " 

norme: clean
	@norminette $(SRCS_VM) $(HEADERS) $(LIBFT_PATH)

re: fclean all

.PHONY:	all clean fclean re
