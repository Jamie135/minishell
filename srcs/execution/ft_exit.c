/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:50:49 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/16 13:50:59 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_print(t_list *list, t_envi *env)
{
	ft_putendl_fd("exit", STDERR);
	ft_putstr_fd("exit: ", STDERR);
	ft_putstr_fd(list->next->content, STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	if (env)
		free_envi(env);
	free_list(list);
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
	
	if (ft_strcmp("exit", list->content) == 0)
	{
		if (list->next && list->next->content)
		{
			if (ft_all_isdigit(list->next->content) && num_cmd == 1)
			{
				if (count_one_minus(list->next->content))
				{
					ft_putendl_fd("exit", STDERR);
					if (env)
						free_envi(env);
					free_list(list);
					exit(251);
				}
				exit_print(list, env);
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
		while (exit_value > 255)
			exit_value -= 256;
		exit(exit_value);
	}
}
