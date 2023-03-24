/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:08:33 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/24 16:35:28 by pbureera         ###   ########.fr       */
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
int			valid_redir_num(t_list *list);
int			valid_arrow_pipe(t_list *list);
int			valid_next_arrow(t_list *list);
int			valid_pipe(t_list *list);

/* exec_1.c */
size_t		num_command(t_list *list);

/* builtins.c */
void		ft_exit(t_list *list, t_envi *env, char *line, t_free *free_var);
static void	ft_exit_alphabet(t_list *list, t_envi *env);

/* free.c */
void		free_ptr(void **ptr);
void		free_envi(t_envi *envi);
void		free_list(t_list *list);
void		free_split(char **tab);

/* message.c */
void		malloc_err(char *str);
int			syntax_err(char *line);
void		print_token(char *str);


#endif
