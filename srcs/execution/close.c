/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:23:05 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/27 17:26:53 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
