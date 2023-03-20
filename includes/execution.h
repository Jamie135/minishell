/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:08:33 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 12:36:03 by pbureera         ###   ########.fr       */
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
t_envi	*init_envi(char **envp);
char	*variable_env(char *env);
char	*value_env(char *env);
t_envi	*cpy_struct_envi(char *ve, char *value, int type);
void	add_back_envi(t_envi **envi, t_envi *cpy);
t_envi	*get_last_envi(t_envi *envi);
t_envi	*null_envi(t_envi *envi);

/* free.c */
void	free_ptr(void **ptr);
void	free_envi(t_envi *envi);
void	free_list(t_list *list);
void	free_split(char **tab);

/* message.c */
void	malloc_err(char *str);
int		syntax_err(char *line);


#endif
