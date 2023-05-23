/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:49:29 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/23 12:48:54 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile int	g_signal;

int	line_dollars_alphabet(char *line, int *exit)
{
	size_t	i;
	int		d;

	i = 0;
	while (line[i] == '$')
		i++;
	if (i == 0 || i == ft_strlen(line) || is_str_alnum_dollars(line))
		return (0);
	else
	{
		d = dollars_pars(line, exit);
		// printf("line: %s ; d=%i\n", line, d);
		return (d);
	}
}

//verifier si la ligne de commande a uniquement que des espaces
int	line_space(char *line, int *exit)
{
	int		i;

	i = 0;
	if (is_str_dot(line))
	{
		if (dots_not_found(line, exit) == -1)
			return (-1);
	}
	if (valid_syntax(line, exit) == -1)
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
	g_signal = 0;
	parent_child_signal(MINISHELL);
	(*count)++;
	line = readline("minishell> ");
	add_history(line);
	if (g_signal == 2)
		*exit = 130;
	parent_child_signal(PARENT);
	if (line_user(line, exit) || line_null(line, env) == -1 \
		|| line_space(line, exit) == -1 \
		|| line_dollars_alphabet(line, exit) == -1)
		return (NULL);
	return (line);
}

//fonction qui lance minishell
int	run(char **envp, char *line, t_list *list, t_free *free_var)
{
	static int		count = 0;
	static int		exit_value = 0;
	static t_envi	*env = NULL;

	env = init_environment(envp);
	if (env == ERROR)
		return (malloc_err("run.c (1)"), EXIT_FAILURE);
	while (1)
	{
		line = ft_readline(line, &count, env, &exit_value);
		if (line == NULL)
			continue ;
		line = command_in_quoted(line);
		if (unfound_command(line, &exit_value))
			continue ;
		list = fill_list(line, free_var, env, &exit_value);
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

// while (list && list->next)
// {
// 	printf("list content: %s ; ", list->content);
// 	printf("type: %i\n", list->type);
// 	list = list->next;
// }

// printf("list content: %s\n", list->content);
// printf("list next content: %s\n", list->next->content);
