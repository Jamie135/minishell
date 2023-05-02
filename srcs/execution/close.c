/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:23:05 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/02 15:19:01 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	can_free(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_num + shell->no_cmd + 1)
	{
		while (shell->redir[i])
		{
			if (!is_str_alnum(shell->redir[i]->content))
				return (-1);
			shell->redir[i] = shell->redir[i]->next;
		}
		i++;
	}
	return (0);
}

void	close_fd(int *fd)
{
	if (*fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	close_pipes(int	**pipes, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		close_fd(&pipes[i][0]);
		close_fd(&pipes[i][1]);
		i++;
	}
}
