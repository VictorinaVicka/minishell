NAME	=	minishell

OBJS	=	$(SRCS:.c)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

LIB		=	../libs/libft/libft.a
PFT		=	../libs/printf/libftprintf.a

PATHLIB =	/libs/libft/

PATHPFT =	/libs/printf/

SRCS 	=	*.c

all		:	$(NAME)
			

$(NAME) : $(SRCS)
			cd ../$(PATHLIB) ; make ; cd ../../ ;
			cd ../$(PATHPFT) ; make ; cd ../ ;
			gcc -o $(NAME) $(CFLAGS) $(SRCS) $(LIB) $(PFT)
			

clean	:
			cd ../$(PATHLIB) ; make clean; cd ../../ ;
			cd ../$(PATHPFT) ; make clean; cd ../../ ;
			$(RM) $(OBJS)

fclean	:	clean
			cd ../libs/libft ; make fclean ; cd .. ;
			$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	clean	fclean	all