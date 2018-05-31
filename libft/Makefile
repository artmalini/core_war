# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakhiny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/24 13:52:27 by amakhiny          #+#    #+#              #
#    Updated: 2017/10/24 13:53:44 by amakhiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
GC = $(CFLAGS) -O2
CFLAGS = -Wall -Wextra -Werror
#SUB_DIR = ft_printf/
O_DIR = ob/
INC1 = -I. libft.h 
INC2 = -I. ft_printf/ft_printf.h
SOURCE = ft_strlen.c ft_strstr.c ft_memdel.c ft_bzero.c ft_strdup.c ft_putnbr.c ft_putchar.c ft_strjoin.c ft_strnew.c ft_memalloc.c \
		ft_strcpy.c ft_strdel.c ft_strsub.c ft_minint.c ft_strchr.c ft_int_length.c ft_atoi.c ft_itoa.c get_next_line.c \
		ft_putstr.c ft_strsplit.c ft_count_words.c ft_getword_len.c ft_strchr.c ft_isdigit.c ft_strcmp.c ft_memcpy.c\
		ft_lstadd.c ft_lstdel.c ft_lstnew.c ft_lstdelone.c ft_strequ.c ft_isalnum.c \
		ft_strncpy.c ft_strncat.c ft_strcat.c \
		\
		ft_printf/build_char_strchar.c ft_printf/build_float_join_str.c ft_printf/build_floats.c ft_printf/build_mantissa_with_build_float.c \
		ft_printf/fill_flag_with_precis.c \
		ft_printf/fill_length_type_hex.c ft_printf/fixsmall.c ft_printf/ft_printf.c ft_printf/ft_strlendup.c ft_printf/nbr_types_cast.c \
		ft_printf/output_chars.c ft_printf/parse_arg.c ft_printf/prf_itoa_base.c \
		ft_printf/print_atoi_nbr.c ft_printf/print_str_with_flags.c ft_printf/str_join_float.c \

OBJ = $(SOURCE:.c=.o)

GREEN		= \033[32m
RED			= \033[31m
DEFAULT		= \033[37m

all: $(NAME)

$(NAME): $(OBJ)
	#@gcc $(GC) -c $(INC1) $(SOURCE) 
	@ar rc $(NAME) $(OBJ)
	@echo "$(GREEN)Libft constructed.$(DEFAULT)"

$(O_DIR)%.o: %.c
	@gcc $(GC) $(INC1) $(INC2) -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Libft erased.$(DEFAULT)"

re: fclean all
