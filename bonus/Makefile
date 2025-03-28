##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for the my_ls program
##

SRC_MAIN	=	../src/main.c

SRC_CORE	=	shell.c

SRC_BUILTIN	=	../src/builtins/builtins.c		\
				../src/builtins/my_cd.c

SRC_CMDS	=	../src/commands/commands.c		\
				../src/commands/executor.c		\
				../src/commands/pipes.c			\
				../src/commands/redirects.c

SRC_PARSER	=	../src/parser/memory.c			\
				../src/parser/parser.c			\
				../src/parser/token.c

SRC_UTILS	=	../src/utils/environment.c		\
				../src/utils/utils.c			\
				../src/utils/usage.c			\
				../src/utils/parser_utils.c		\
				../src/utils/pipe_utils.c

SRC			=	$(SRC_CORE)						\
				$(SRC_BUILTIN)					\
				$(SRC_CMDS)						\
				$(SRC_PARSER)					\
				$(SRC_UTILS)

OBJ			=	$(SRC:.c=.o)					\
				$(SRC_MAIN:.c=.o)

CFLAGS		=   -Wall -Wextra -Werror -iquote ../include
LIBFLAGS	=	-L ../lib/ -lmy
LIB_MAKE	=	make -C ../lib/my
RM			=	rm -f
CP			=	cp
CC			=	gcc

NAME		=	mysh

all:			clib $(NAME)

clib:
		$(LIB_MAKE)
		$(CP) bonus.h ../include

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS)

clean:
		$(RM) $(OBJ)
		$(RM) $(MAIN_OBJ)
		$(RM) $(TEST_OBJ)

fclean:			clean
		$(RM) $(NAME)
		$(RM) $(TEST_NAME)
		$(RM) ../include/bonus.h
		$(LIB_MAKE) fclean

re:				fclean all


.PHONY:			all clean fclean all
