/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:10:41 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 15:15:08 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redir(t_list **list, int n)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (i < n)
	{
		while (list[i])
		{
			tmp = list[i]->next;
			free_ptr((void **)&list[i]);
			list[i] = tmp;
		}
		i++;
	}
	free(list);
}

void	free_pipes(int **pipes, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free_ptr((void **)&pipes[i]);
		i++;
	}
	free_ptr((void **)&pipes);
}

void	free_args(char ***args, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free_split(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}
