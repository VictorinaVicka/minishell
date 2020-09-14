# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/10 15:33:42 by qsymond           #+#    #+#              #
#    Updated: 2020/08/30 23:35:47 by qsymond          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

RM = rm -rf

NAME = libft.a

SRCS =	*.c

OBJS = -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(OBJS) $(SRCS)
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all