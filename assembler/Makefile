# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/30 13:55:02 by amakhiny          #+#    #+#              #
#    Updated: 2018/05/30 13:55:17 by amakhiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../asm
FLAGS		= -Wall -Wextra -Werror
CC			= gcc -g

HEADERS		= ../includes
HEADERS_L	= ../libft/includes
LIBFT		= -L ../libft -lft
LIBFT_PATH	= ../libft

SRCS_ASM	=	asm_check_args.c \
                asm_cmd.c \
				asm_create_cor.c \
				asm_create_cor_fpos_opc.c \
				asm_create_cor_instr.c \
				asm_errors.c \
				asm_free_struct.c \
				asm_init_and_free.c \
				asm_label.c \
				asm_main.c \
				asm_name_cmt_valid.c \
				asm_parse_line.c \
				asm_parse_main.c \
				asm_print.c \
				asm_recalc_cmd_links.c \
				asm_valid_main.c

OBJS_ASM	=   $(SRCS_ASM:.c=.o)

RED			= \033[31m
GREEN		= \033[32m
CYAN		= \033[36m
GREY		= \033[37m

all: $(NAME)

$(NAME): $(OBJS_ASM)
	@$(CC) $(OBJS_ASM) $(FLAGS) -I $(HEADERS) -I $(HEADERS_L) $(LIBFT) -o $@
	@echo "\033[0;32m ----> Created (assembler)"

$(OBJS_ASM): %.o: %.c
	@$(CC) -c $(FLAGS) -I $(HEADERS) -I $(HEADERS_L) $< -o $@
	@echo "\033[0;36m ----> Created object files (assembler)"

clean:
	@rm -f $(OBJS_ASM)
	@echo "\033[0;31m ----> Delete object files [assembler]"

fclean:	clean
	@rm -f $(NAME)
	@echo "\033[0;31m ----> Delete [asm] " 

norme: clean
	@norminette $(SRCS_ASM) $(HEADERS) $(LIBFT_PATH)

re: fclean all

.PHONY:	all clean fclean re
