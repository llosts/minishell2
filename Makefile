##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for the my_ls program
##

SRC_MAIN	=	src/main.c

SRC_CORE	=	src/shell.c

SRC_BUILTIN	=	src/builtins/builtins.c		\
				src/builtins/my_cd.c

SRC_CMDS	=	src/commands/commands.c		\
				src/commands/executor.c		\
				src/commands/pipes.c		\
				src/commands/redirects.c

SRC_PARSER	=	src/parser/memory.c			\
				src/parser/parser.c			\
				src/parser/token.c

SRC_UTILS	=	src/utils/environment.c		\
				src/utils/utils.c			\
				src/utils/usage.c			\
				src/utils/parser_utils.c	\
				src/utils/pipe_utils.c

SRC_BONUS	=	bonus/shell.c

SRC			=	$(SRC_CORE)					\
				$(SRC_BUILTIN)				\
				$(SRC_CMDS)					\
				$(SRC_PARSER)				\
				$(SRC_UTILS)

OBJ			=	$(SRC:.c=.o)				\
				$(SRC_MAIN:.c=.o)

OBJ_BONUS	=	$(SRC_BONUS:.c=.o)			\
				$(SRC_BUILTIN:.c=.o)		\
				$(SRC_CMDS:.c=.o)			\
				$(SRC_PARSER:.c=.o)			\
				$(SRC_UTILS:.c=.o)			\
				$(SRC_MAIN:.c=.o)			\

LIBFLAGS	=	-L lib/ -lmy
CFLAGS		=   -Wall -Wextra -Werror -iquote include
BONUSFLAGS	=	-iquote bonus
LIB_MAKE	=	make -C lib/my
RM			=	rm -f
CP			=	cp
CC			=	gcc

NAME		=	mysh

all:			clib $(NAME)

clib:
		$(LIB_MAKE)

debug: 	CFLAGS += -g3 -fsanitize=address
debug: 	re

bonus:	clib $(OBJ_BONUS)
		$(CC) -o $(NAME) $(OBJ_BONUS) $(CFLAGS) $(LIBFLAGS) $(BONUSFLAGS)

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS)

clean:
		$(RM) $(OBJ)
		$(RM) $(MAIN_OBJ)
		$(RM) $(TEST_OBJ)
		$(RM) $(OBJ_BONUS)

fclean:			clean
		$(RM) $(NAME)
		$(RM) $(TEST_NAME)
		$(RM) include/bonus.h
		$(LIB_MAKE) fclean

re:				fclean all

.PHONY:			all clean fclean all debug
