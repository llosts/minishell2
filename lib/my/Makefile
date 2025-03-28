##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for the lib compilation
##

SRC =		my_strdup.c				\
			my_strcmp.c				\
			my_strncmp.c			\
			my_strlen.c				\
			my_putstr.c				\
			my_strcat.c				\
			my_strcpy.c				\
			my_strncpy.c			\
			my_strchr.c				\
			my_isalpha.c			\
			my_isalnum.c			\
			my_strtok.c				\
			my_str_to_word_array.c	\

OBJ =		$(SRC:.c=.o)

CC =		gcc -c
CLIB =		ar rc
CFLAGS =	-Wall -Werror -Wextra
INCLUDE =	-iquote .
HEADER =	my.h
RM =		rm -f
CP =		cp

NAME =		libmy.a

$(NAME):	$(OBJ)
			$(CC) $(SRC) $(CFLAGS) $(INCLUDE)
			$(CLIB) $(NAME) $(OBJ)
			$(CP) $(HEADER) ../../include
			$(CP) $(NAME) ../

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:     clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)
			$(RM) ../../include/$(HEADER)

re:			fclean all

.PHONY:		all clean fclean re
