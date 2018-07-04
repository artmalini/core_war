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
LD			= -lncurses

HEADERS		= ../includes
HEADERS_L	= ../libft/includes
LIBFT		= -L ../libft -lft
LIBFT_PATH	= ../libft

SRCS_VM	=	vm_errors.c \
			vm_load.c \
			vm_main.c \
			vm_ncurses.c \
			vm_params.c \
			vm_print.c \
			vm_read.c \
			op.c \

OBJS_VM	=   $(SRCS_VM:.c=.o)

RED			= \033[31m
GREEN		= \033[32m
CYAN		= \033[36m
GREY		= \033[37m

all: $(NAME)

$(NAME): $(OBJS_VM)
	@$(CC) $(LD) $(OBJS_VM) $(FLAGS) -I $(HEADERS) -I $(HEADERS_L) $(LIBFT) -o $@
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
