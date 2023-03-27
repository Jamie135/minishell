/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:08:33 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/27 17:27:05 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

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
	int		cmd_id;
	int		cmd_num;
	int		redir_num;
	t_list	**redir;
	int		*infile;
	int		*outfile;
	pid_t	*pid;
	int		**pipes;
	char	***args;
	int		status;
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

typedef enum e_fd
{
	STDIN,
	STDOUT,
	STDERR
}	t_fd;

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

/* execution.c */
t_envi		*execution(t_list *list, t_envi *env, int *count, int *exit_value);

/* valid_parsing.c */
int			valid_num_redir(t_list *list);
int			valid_extra_token(t_list *list);
int			valid_after_redir(t_list *list);
int			valid_pipe(t_list *list);

/* heredoc.c */
int			heredoc(t_list *list, t_envi *env, int *count, int *exit_value);
int			heredoc_init(t_heredoc *heredoc, t_list *list);
void		heredoc_exec(t_heredoc *heredoc, char *limiter, char *name);

/* heredoc_utils.c */
char		*random_string(int len);

/* exec_1.c */
size_t		num_command(t_list *list);

/* builtins.c */
void		ft_exit(t_list *list, t_envi *env, char *line, t_free *free_var);
static void	ft_exit_alphabet(t_list *list, t_envi *env);

/* close.c */
void		close_fd(int *fd);
void		close_pipes(int	**pipes, size_t num);

/* free.c */
void		free_ptr(void **ptr);
void		free_envi(t_envi *envi);
void		free_list(t_list *list);
void		free_split(char **tab);
void		free_heredoc(t_heredoc *heredoc, char *limiter, char *line, int fd);

/* message.c */
void		malloc_err(char *str);
int			syntax_err(char *line);
void		print_token(char *str);
void		message_heredoc(t_heredoc *heredoc, char *str, int n, void (*f)(int));


#endif
