/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:53:52 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 17:24:04 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_alphabet(t_list *list, t_envi *env)
{
	const int	num_cmd = num_command(list);
	
	if (ft_strcmp("exit", list->content) == 0)
	{
		if (list->next && list->next->content)
		{
			if (ft_all_isdigit(list->next->content) && num_cmd == 1)
			{
				ft_putendl_fd("exit", STDERR);
				ft_putstr_fd("exit: ", STDERR);
				ft_putstr_fd(list->next->content, STDERR);
				ft_putendl_fd(": numeric argument required", STDERR);
				if (env)
					ft_free_envi(env);
				ft_free_lst(list);
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
