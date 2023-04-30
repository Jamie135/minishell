/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:50:49 by Espéranto         #+#    #+#             */
/*   Updated: 2023/04/30 12:25:45 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_alphabet_print(t_list *list, t_envi *env)
{
	ft_putendl_fd("exit", STDERR);
	ft_putstr_fd("exit: ", STDERR);
	ft_putstr_fd(list->next->content, STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	if (env)
		free_envi(env);
	free_list(list);
}

int	exit_negative_print(t_list *list, t_envi *env)
{
	int	abs;

	abs = ft_atoi((const char *)list->next->content);
	ft_putendl_fd("exit", STDERR);
	if (env)
		free_envi(env);
	free_list(list);
	while (abs < 256)
		abs += 256;
	return (abs);
}

int	count_one_minus(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_alphabet(t_list *list, t_envi *env)
{
	const int	num_cmd = num_command(list);
	int			abs;

	if (ft_strcmp("exit", list->content) == 0)
	{
		if (list->next && list->next->content)
		{
			if (ft_all_isdigit(list->next->content) && num_cmd == 1)
			{
				if (count_one_minus(list->next->content))
				{
					abs = exit_negative_print(list, env);
					exit(abs);
				}
				exit_alphabet_print(list, env);
				exit(2);
			}
		}
	}
}

void	ft_exit(t_list *list, t_envi *env, char *line, t_free *free_var)
{
	const size_t	size = ft_lstsize(list);
	int				exit_value;

	exit_value = 0;
	free(free_var->unexpended);
	free(free_var->split);
	free(free_var->quoted);
	free(line);
	exit_alphabet(list, env);
	if (ft_strcmp(list->content, "exit") == 0 && size <= 2)
	{
		if (list->next && list->next->content)
			exit_value = ft_atoi(list->next->content);
		ft_putendl_fd("exit", STDERR);
		if (env)
			free_envi(env);
		free_list(list);
		exit(exit_value);
	}
}
