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
CC			= gcc

HEADERS		= ../includes
HEADERS_L	= ../libft/includes
LIBFT		= -L ../libft -lft
LIBFT_PATH	= ../libft

SRCS_ASM	=	main.c \
				op.c \
				error_handler.c \
				name_and_cmt_valid.c \

OBJS_ASM	=   $(SRCS_ASM:.c=.o)

RED			= \033[31m
GREEN		= \033[32m
CYAN		= \033[36m
GREY		= \033[37m

all: $(NAME)

$(NAME): $(OBJS_ASM)
	@$(CC) $(OBJS_ASM) $(FLAGS) -I $(HEADERS) -I $(HEADERS_L) $(LIBFT) -o $@
	@echo "\033[0;32m ----> Created (Core_ASM)"

$(OBJS_ASM): %.o: %.c
	@$(CC) -c $(FLAGS) -I $(HEADERS) -I $(HEADERS_L) $< -o $@
	@echo "\033[0;36m ----> Created object files (Core_ASM)"

clean:
	@rm -f $(OBJS_ASM)
	@echo "\033[0;31m ----> Delete object files [Core_ASM]"

fclean:	clean
	@rm -f $(NAME)
	@echo "\033[0;31m ----> Delete [asm] " 

norme: clean
	@norminette $(SRCS_ASM) $(HEADERS) $(LIBFT_PATH)

re: fclean all

.PHONY:	all clean fclean re


# $(NAME):$(OBJS)
# 	@$(CC) $(CFLAG) $(SRCS) $(LIBFT) -o $(NAME)