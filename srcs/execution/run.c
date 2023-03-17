/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:49:29 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/17 16:54:40 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '\'' && i++)
		{
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (syntax_err(line));
		}
		else if (line[i] && line[i] == '\"' && i++)
		{
			while (line[i] && line[i] != '\"')
				i++;
			if (!line[i])
				return (syntax_err(line));
		}
		if (line[i] && (line[i] == ';' || line[i] == 92))
			return (syntax_err(line));
		i++;
	}
	return (0);
}

int	line_space(char *line)
{
	int	i;

	i = 0;
	if (valid_syntax(line) == -1)
		return (-1);
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	free(line);
	return (-1);
}

int	line_null(char *line, t_envi *env)
{
	if (line == NULL)
	{
		ft_putendl_fd("exit", STDOUT);
		free_envi(env);
		exit(0);
	}
	if (line[0] == '\0')
	{
		free(line);
		return (-1);
	}
	return (0);
}

// lire et ajouter en historique la ligne "minishell> "
char	*ft_readline(char *line, int *count, t_envi *env, int *exit)
{
	(*count)++;
	line = readline("minishell> ");
	add_history(line);
	if (line_null(line, env) == -1 || line_space(line) == -1)
		return (NULL);
	return (line);
}

// fonction commande ()
int	run(char **envp, char *line, t_list *list, t_free *to_free)
{
	static int		count;
	static int		exit;
	static t_envi	*env;

	count = 0;
	exit = 0;
	env = NULL;
	env = init_envi(envp);
	if (env == NULL)
		env = null_envi(env);
	if (env == -1)
		return (malloc_err("main.c"), EXIT_FAILURE);
	while (1)
	{
		line = ft_readline(line, &count, env, exit);
		if (line == NULL)
			continue ;
		list = fill_list(line, to_free);
		if (list == NULL)
			continue;
		if (free_null_list(list, to_free, line, env) == EXIT_SUCCESS)
			continue;
	}
}
