# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 10:26:26 by amakhiny          #+#    #+#              #
#    Updated: 2018/02/24 10:26:30 by amakhiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = compiling

LIB_DIR = ./libft
ASM_DIR = ./assembler

RED		= \033[31m
GREEN	= \033[32m
CYAN	= \033[36m
GREY	= \033[37m

all: $(NAME)

$(NAME): 
	#@make -C $(LIB_DIR)
	@make -C $(ASM_DIR)

clean:
	#@make -C $(LIB_DIR) clean
	@make -C $(ASM_DIR) clean

fclean: clean
	#@make -C $(LIB_DIR) fclean
	@make -C $(ASM_DIR) fclean
	
re: fclean all

.PHONY:		all clean fclean re
	