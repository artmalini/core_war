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

SRCS_ASM	=	cmd_asm.c \
                create_cor.c \
				debug_asm.c \
				error_handler.c \
				free_asm.c \
				label_asm.c \
				main.c \
				name_and_cmt_valid.c \
				op.c \
				parse_asm.c \
				settings.c \
				valid_main.c \
				check_args.c \

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
