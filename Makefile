NAME = minishell

SRC = srcs/execution/environment_1.c srcs/execution/environment_2.c \
srcs/execution/environment_3.c srcs/execution/environment_4.c srcs/execution/environment_5.c \
srcs/execution/execution.c \
srcs/execution/message_1.c srcs/execution/message_2.c \
srcs/execution/args.c srcs/execution/builtins.c \
srcs/execution/parent.c srcs/execution/child_1.c srcs/execution/child_2.c \
srcs/execution/close.c srcs/execution/open.c srcs/execution/command.c \
srcs/execution/expend.c srcs/execution/expend_utils.c \
srcs/execution/free_execution_1.c srcs/execution/free_execution_2.c \
srcs/execution/free_execution_3.c \
srcs/execution/ft_cd.c srcs/execution/ft_cd_2.c srcs/execution/ft_echo.c srcs/execution/ft_env.c \
srcs/execution/ft_exit.c srcs/execution/ft_export.c srcs/execution/ft_pwd.c \
srcs/execution/ft_unset.c \
srcs/execution/heredoc.c srcs/execution/heredoc_utils.c \
srcs/execution/shell_redir.c srcs/execution/shell_struct.c srcs/execution/shell_utils.c \
srcs/execution/utils.c srcs/execution/utils_2.c srcs/execution/valid_parsing.c \
srcs/execution/utils_3.c \
srcs/minishell.c srcs/run.c srcs/signal.c \
\
srcs/parsing/list.c srcs/parsing/type.c srcs/parsing/trim.c srcs/parsing/trim_utils.c \
srcs/parsing/free_parsing_1.c srcs/parsing/free_parsing_2.c \
srcs/parsing/quote.c srcs/parsing/quote_utils.c \
srcs/parsing/split_line.c srcs/parsing/split_line_utils.c srcs/parsing/split_pipe.c \
srcs/parsing/string.c srcs/parsing/string_utils.c srcs/parsing/utils_parsing.c \
srcs/parsing/string_quote.c srcs/parsing/expend_pars.c srcs/parsing/utils_parsing2.c \
srcs/parsing/inside_quote.c

OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -MMD -g3 -fsanitize=address -lreadline

all: $(NAME)

%.o: %.c $(CC) $(FLAGS) -c $(SRC)

$(NAME):	libft/libft.a $(OBJ)
	$(CC) $(OBJ) libft/libft.a -o $(NAME) $(FLAGS)

libft/libft.a:
	cd libft && make && cd ..

clean:
	cd libft && make clean && cd ..
	rm -f $(OBJ)

fclean:	clean
	make fclean -C ./libft
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
