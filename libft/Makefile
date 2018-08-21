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
#CFLAGS = -Wall -Wextra -Werror
PRINTF_DIR = ft_printf/
INC1 =  includes/
#INC1 = -I libft.h 
#INC2 = -I ft_printf/ft_printf.h
LIB_SOURCE = ft_strlen.c ft_strstr.c ft_memdel.c ft_bzero.c ft_strdup.c ft_putnbr.c ft_putchar.c ft_strjoin.c ft_strnew.c ft_memalloc.c \
		ft_strcpy.c ft_strdel.c ft_strsub.c ft_minint.c ft_strchr.c ft_int_length.c ft_atoi.c ft_itoa.c get_next_line.c \
		ft_putstr.c ft_strsplit.c ft_count_words.c ft_getword_len.c  ft_isdigit.c ft_strcmp.c ft_memcpy.c\
		ft_lstadd.c ft_lstdel.c ft_lstnew.c ft_lstdelone.c ft_strequ.c ft_isalnum.c ft_isalpha.c \
		ft_strncpy.c ft_strncat.c ft_strcat.c ft_strncmp.c ft_putchar_fd.c \
		ft_strncpy.c ft_strncat.c ft_strcat.c ft_strncmp.c ft_atoi_base.c ft_strjoinstr.c \

		
LIB_OBJ = $(LIB_SOURCE:.c=.o)
PRINTF_SOURCE =	build_char_strchar.c build_float_join_str.c build_floats.c build_mantissa_with_build_float.c \
		fill_flag_with_precis.c \
		fill_length_type_hex.c fixsmall.c ft_printf.c ft_strlendup.c nbr_types_cast.c \
		output_chars.c parse_arg.c prf_itoa_base.c \
		print_atoi_nbr.c print_str_with_flags.c str_join_float.c
PRINTF_OBJ = $(addprefix $(PRINTF_DIR), $(PRINTF_SOURCE:.c=.o))

GREEN		= \033[32m
RED			= \033[31m
DEFAULT		= \033[37m

ifeq ($(shell uname),Darwin)
	ECHO = echo
else
	ECHO = echo -e
endif

all: $(NAME)

$(NAME): $(LIB_OBJ) $(PRINTF_OBJ)
	@ar rc $@ $^
	@ar -s $@
	@$(ECHO) "$(GREEN)Libft constructed.$(DEFAULT)"

%.o:
	@$(ECHO) "\r$(GREEN) Compiling $@                \c\033[K"
	@gcc $(GC) -c -o $@ $(@:.o=.c) -I $(INC1)

clean:
	@rm -f $(LIB_OBJ) $(PRINTF_OBJ)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Libft erased.$(DEFAULT)"

re: fclean all

.PHONY: clean fclean re all
