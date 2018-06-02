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

NAME	=	../asm
CC		=   gcc
#CFLAGS	= 	-Wall -Wextra -Werror
LIBFT	=	 -L../libft -lft

SRCS	=	main.c op.c error_handler.c name_and_cmt_valid.c \

OBJS	=   $(SRCS:.c=.o)


all:	$(NAME)

$(NAME):$(OBJS)
	@$(CC) $(CFLAG) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
