# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/23 19:22:41 by qsymond           #+#    #+#              #
#    Updated: 2020/08/29 18:51:01 by qsymond          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSC		= $(shell find srcs -type f -name 'ft_*.c')
SRCSH		= includes/ft_printf.h
OBJS		= $(SRCSC:%.c=%.o)
NAME		= libftprintf.a
CC			= gcc
AR			= ar -rc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o : %.c
	gcc -Wall -Wextra -Werror -Iincludes -o $@ -c $<

clean:
	$(RM) $(OBJS)

bonus: $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all