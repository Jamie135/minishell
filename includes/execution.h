/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:08:33 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 16:16:49 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

# define SUCCESS 0
# define FAILURE -1
# define ERROR (void *)-1

typedef struct s_envi
{
	char			*ve;
	char			*value;
	int				type;
	struct s_envi	*next;
}	t_envi;

typedef struct s_shell
{
	t_list	*list;
	char	**environment;
	t_envi	*envi;
	int		cid;
	int		cmd_num;
	int		no_cmd;
	int		redir_num;
	t_list	**redir;
	int		*infile;
	int		*outfile;
	pid_t	*pid;
	int		**pipes;
	char	***args;
	int		mode;
	int		*line_num;
	int		*exit_value;
}	t_shell;

typedef struct s_heredoc
{
	t_list	*list;
	t_envi	*envi;
	int		*line_num;
	int		*exit_value;
}	t_heredoc;

typedef enum e_filemode
{
	INFILE,
	OUTFILE,
}	t_mode;

typedef enum e_fd
{
	STDIN,
	STDOUT,
	STDERR
}	t_fd;

typedef enum e_redir
{
	TO_INFILE,
	TO_OUTFILE,
	APPEND
}	t_redir;

typedef enum e_error
{
	MALLOC = -1,
	SYNTAX = -2,
	PATH = -3,
	COMMAND = -4,
	EXIT = -5
}	t_error;

enum e_value
{
	VALID,
	UNVALID
};

/* environment.c */
t_envi		*init_envi(char **envp);
char		*variable_env(char *env);
char		*value_env(char *env);
t_envi		*cpy_struct_envi(char *ve, char *value, int type);
void		add_back_envi(t_envi **envi, t_envi *cpy);
t_envi		*get_last_envi(t_envi *envi);
t_envi		*null_envi(t_envi *envi);
char		*find_value_envi(char *name, t_envi *envi);
char		**init_env(t_envi *envi);
size_t		len_envi(t_envi *envi);
t_envi		*update_value_envi(char *ve, char *value, int type, t_envi *envi);
void		print_envi(t_shell *shell, t_envi *envi);

/* execution.c */
t_envi		*execution(t_list *list, t_envi *env, int *count, int *exit_value);
void		shlvl_var(t_shell *shell);

/* valid_parsing.c */
int			valid_num_redir(t_list *list);
int			valid_extra_token(t_list *list);
int			valid_after_redir(t_list *list);
int			valid_pipe(t_list *list);

/* heredoc.c */
int			heredoc(t_list *list, t_envi *env, int *count, int *exit_value);
int			heredoc_init(t_heredoc *heredoc, t_list *list);
void		heredoc_exec(t_heredoc *heredoc, char *limiter, char *name, int signal_flag);
char		*heredoc_get_line(t_heredoc *heredoc, char *limiter, int fd);
void		heredoc_unlink(t_list *list);

/* heredoc_utils.c */
char		*random_string(int len);
void		heredoc_error(t_heredoc *heredoc, char *limiter, int fd);
void		exit_heredoc(t_heredoc *heredoc, char *limiter, char *line, int fd);

/* expend.c */
char		*expend_str(t_envi *envi, char *str, int exit_value);
char		*expend_var(t_envi *envi, char *str, int exit_value);
char		*expend_join(t_envi *envi, t_list **join, char *str);
int			expend_exit(char *str, t_list **join, int exit_value);
int			expend_list(t_envi *envi, t_list *list, int exit_value);

/* expend_utils.c */
char		*add_space_to_dollars(char *str);
size_t		count_dollar(char *str);
char		*add_value_to_ve(char *ve, t_envi *envi);
int			is_special_var(char c);
int			is_dollar(char *str);

/* shell_struct.c */
t_shell		*shell_struct(t_list *list, t_envi *envi, int *count, int *exit_value);
int			init_shell(t_shell *shell, t_list *list);
pid_t		*init_pid(t_shell *shell);
char		***init_args(t_shell *shell, t_list *list);
int			**init_pipes(t_shell *shell);

/* shell_redir.c */
int			list_redir(t_shell *shell, t_list *list);
int			no_cmd_list_redir(t_shell *shell, t_list *list, t_list **redir);
int			cmd_list_redir(t_shell *shell, t_list *list, t_list **redir);
int			type_redir(char *str, int type[2]);

/* shell_utils.c */
void		valid_next(t_shell *shell, t_list *list, int type[2], int *i);
int			mode_file(int mode, int type[2]);

/* shell_mode.c */
int			parent_no_cmd(t_shell *shell);
int			parent_one_cmd(t_shell *shell);

/* child.c */
void		child_cmd(t_shell *shell);
void		child_no_cmd(t_shell *shell);

/* command.c */
size_t		num_command(t_list *list);
size_t		num_redir(t_list *list);

/* args.c */
char		**list_args(t_list *list);
size_t		len_args(t_list *list);
int			check_space_cmd(t_list *list);
int			split_space_cmd(t_list *list, char **args, size_t *i);
int			before_space(char *str);

/* builtins.c */
int			builtins_parent(t_shell *shell);
int			builtins_child(t_shell *shell);
void		ft_cd(char **arg);
void		ft_echo(t_envi *envi, char **arg);
void		ft_env(t_envi *envi);
void		ft_exit(char **arg);
int			ft_export(t_envi *envi, char **arg);
void		ft_pwd(void);
void		ft_unset(t_envi *envi, char **arg);

/* open.c */
int			open_infile(t_shell *shell, t_list *redir);
int			open_outfile(t_shell *shell, t_list *redir);
int			open_file(char *name, t_redir type);

/* close.c */
void		close_fd(int *fd);
void		close_pipes(int	**pipes, size_t num);

/* exit.c */
void		ft_exit(t_list *list, t_envi *env, char *line, t_free *free_var);
static void	ft_exit_alphabet(t_list *list, t_envi *env);

/* utils.c */
int			is_str_alnum(char *str);
int			len_array(char **args);
void		pid_return(int mode);

/* free_execution.c */
void		free_ptr(void **ptr);
void		free_envi(t_envi *envi);
void		free_list(t_list *list);
void		free_split(char **tab);
void		free_heredoc(t_heredoc *heredoc, char *limiter, char *line, int fd);
void		free_one_envi(t_envi *envi);
void		free_n_split(char **split, int n);
void		free_shell_1(t_shell *shell);
void		free_redir(t_list **list, int n);
void		free_pipes(int **pipes, size_t n);
void		free_args(char ***args, size_t n);

/* message.c */
void		malloc_err(char *str);
int			syntax_err(char *line);
void		print_token(char *str);
void		message_heredoc(t_heredoc *heredoc, char *str, int n, void (*f)(int));
void		message_free_exit(t_shell *shell, char *str, int value, void (*f)(int));


#endif
