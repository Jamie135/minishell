NAME =	minishell

AR =	ar rcs

CC =	cc

CFLAGS :=	-Wall -Wextra -Werror -MMD -g3

CFLAGS_DEBUG :=	-Wall -Wextra -Werror -MMD -g3 -fsanitize=address

RM :=	rm -rf

MKDIR :=	mkdir -p

LIBFT_DIR :=	libft/

LIBFT :=	ft_isalnum.c ft_atoi_long.c ft_atoi.c ft_bzero.c ft_calloc.c ft_memchr.c \
		ft_all_isdigit.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_strrchr.c ft_strtrim.c \
		ft_lstadd.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstjoin.c \
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_lstprint_type.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c ft_strchr.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_substr.c \
		ft_strjoin.c ft_strlcat.c ft_strcmp.c ft_strjoin_all.c ft_tolower.c \
		ft_strdup.c ft_striteri.c ft_strnstr.c ft_strlcpy.c ft_strlen.c \
		ft_strmapi.c ft_strncmp.c get_next_line_utils.c get_next_line.c

SRCS_LIBFT :=	${addprefix ${LIBFT_DIR},${LIBFT}}

DIRECTORY :=	srcs/

FILES :=	minishell.c run.c parsing/free_parsing_1.c parsing/free_parsing_2.c \
		parsing/list.c parsing/quote_utils.c parsing/quote.c parsing/split_line.c \
		parsing/split_line_utils.c parsing/split_pipe.c parsing/string_utils.c \
		parsing/string.c parsing/trim_utils.c parsing/trim.c parsing/type.c \
		execution/args.c execution/builtins.c execution/child_1.c execution/exit.c \
		execution/child_2.c execution/close.c execution/command.c execution/open.c \
		execution/environnement_1.c execution/environnement_2.c execution/ft_cd.c \
		execution/environnement_3.c execution/environnement_4.c execution/ft_env.c \
		execution/environnement_5.c execution/execution.c execution/expend_utils.c \
		execution/expend.c execution/free_execution_1.c execution/free_execution_2.c \
		execution/free_execution_3.c execution/ft_echo.c execution/ft_export.c \
		execution/ft_exit.c execution/ft_pwd.c execution/ft_unset.c execution/utils.c \
		execution/heredoc_utils.c execution/heredoc.c execution/message_1.c \
		execution/message_2.c execution/parent.c execution/shell_struct.c \
		execution/shell_redir.c execution/shell_utils.c execution/valid_parsing.c

SRCS :=	${addprefix ${DIRECTORY},${FILES}}

LIB_DIR := ./lib

DIR := ./objs/

OBJS_LIBFT :=	${SRCS_LIBFT:.c=.o}

OBJS_LIBFT :=	$(addprefix $(DIR),$(OBJS_LIBFT))

OBJS :=	${SRCS:.c=.o}

OBJS :=	$(addprefix $(DIR),$(OBJS))

DEPS := ${OBJS:.o=.d} ${OBJS_LIBFT:.o=.d}

all :	${NAME}

${NAME} :	${OBJS_LIBFT} ${OBJS}
			@${MKDIR} ${LIB_DIR}
			@${AR} ${LIB_DIR}libft.a ${OBJS_LIBFT}
			@{CC} ${CFLAGS} ${OBJS} -L ${LIB_DIR} -lft -lreadline -o ${NAME}

.PHONY	: all clean fclean re test
