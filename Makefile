NAME		=	minishell

SRC			=	src
INC			=	include
OBJ			=	obj

HFILES		=	tokenizer.h parser.h print.h phrase.h execution.h my_env.h\
				signal_handler.h
HEADERS		=	$(addprefix $(INC)/, $(HFILES))

CFILES		=	main.c tokenizer.c tokenizer_utils.c error.c parser.c parser2.c\
				phrase.c print.c exec_bin.c exec_cmd1.c exec_cmd2.c\
				exec_control.c exec_utils.c exec_operation.c\
				signal_handler.c
OFILES		=	$(CFILES:.c=.o)
OBJS		=	$(addprefix $(OBJ)/, $(OFILES))
SRCS		=	$(addprefix $(SRC)/, $(CFILES))

FTDIR		=	libft
LIBFT		=	ft
MAKELIBFT	=	$(MAKE) -C $(FTDIR)

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf

VPATH		= $(SRC)

$(OBJ)/%.o:	%.c
			$(CC) $(CFLAGS) -I$(INC) -I$(FTDIR) -c $< -o $@

$(NAME):	$(OBJ) $(OBJS)
			@$(MAKELIBFT)
			$(CC) $(OBJS) -L$(FTDIR) -l$(LIBFT) -lreadline -o $(NAME)

$(OBJ):
			@mkdir -p $(OBJ)

all:		$(NAME)

clean:
			@$(MAKELIBFT) clean
			@$(RM) $(OBJS)

fclean:		clean
			@$(MAKELIBFT) fclean
			@$(RM) $(NAME)

re:			fclean all

norme:
			@$(MAKELIBFT) norme
			@norminette $(SRCS) $(HEADERS)

.PHONY:		all clean fclean re norme
