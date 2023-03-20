/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:20:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 16:22:37 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_quote(char *str)
{
	ft_putendl_fd("syntax error", 2);
	free(str);
	return (NULL);
}

void	free_line_and_split(char *line, char **split)
{
	free_ptr((void **)&line);
	free(split);
}

int	free_null_list(t_list *list, t_free *free_var, char *line, t_envi *env)
{
	if (list == NULL)
	{
		free_line_and_split(line, free_var->split);
		free(free_var->unexpended);
		free(free_var->quoted);
		free_envi(env);
		free_list(list);
		ft_putendl_fd("exit", STDOUT);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	*free_fill(char **tab, t_list *list, char *str)
{
	if (tab)
	{
		ft_putendl_fd("syntax error", 2);
		free_split(tab);
	}
	free(list);
	free(str);
	return (NULL);
}

int	free_trim(t_free *free_var, int i)
{
	free_split_index(free_var->split, i, 0);
	free(free_var->unexpended);
	free(free_var->quoted);
	return (-1);
}
