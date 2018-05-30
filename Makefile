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

#INC = -I ./libft
#FLAGS = -Wall -Wextra -Werror -O2 -I.
LIB_DIR = ./libft
ASM_DIR = ./core_asm

RED		= \033[31m
GREEN	= \033[32m
CYAN	= \033[36m
GREY	= \033[37m

all: $(NAME)

$(NAME): 
	@make -C $(LIB_DIR)
	@make -C $(ASM_DIR)
	#@echo " $(CYAN)$(NAME) $(GREY)generated \xF0\x9F\x98\xBA"

clean:
	@make -C $(LIB_DIR) clean
	@make -C $(ASM_DIR) clean
	#@echo " $(RED)All objects has been deleteted!"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@make -C $(ASM_DIR) fclean
	#@echo " $(RED)$(NAME)$(GREY) has been deleteted!"

re: fclean all

.PHONY:		all clean fclean re
