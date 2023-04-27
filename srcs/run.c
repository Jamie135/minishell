/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:49:29 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/25 17:12:08 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile int	signal_flag;

//verifier si la syntaxe est correcte (ouverture et fermeture des quotes)
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

//verifier si la ligne de commande a uniquement que des espaces
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

//verifier si la ligne de commande est vide
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

//retourner la ligne de commande lue par readline en l'ajoutant en historique
char	*ft_readline(char *line, int *count, t_envi *env, int *exit)
{
	signal_flag = 0;
	sig();
	(*count)++;
	line = readline("minishell> ");
	add_history(line);
	parent_heredoc_signal(PARENT);
	if (line_null(line, env) == -1 || line_space(line) == -1)
		return (NULL);
	return (line);
}

//fonction qui lance minishell
int	run(char **envp, char *line, t_list *list, t_free *free_var)
{
	static int		count;
	static int		exit_value;
	static t_envi	*env;

	count = 0;
	exit_value = 0;
	env = NULL;
	env = init_envi(envp);
	if (env == NULL)
		env = null_envi(env);
	if (env == ERROR)
		return (malloc_err("run.c (1)"), EXIT_FAILURE);
	while (1)
	{
		line = ft_readline(line, &count, env, &exit_value);
		if (line == NULL)
			continue ;
		list = fill_list(line, free_var);
		if (list == NULL)
			continue ;
		if (free_null_list(list, free_var, line, env) == EXIT_SUCCESS)
			continue ;
		ft_exit(list, env, line, free_var);
		env = execution(list, env, &count, &exit_value);
		if (env == ERROR)
			return (malloc_err("run.c (2)"), EXIT_FAILURE);
	}
}
