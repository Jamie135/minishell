/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:33:31 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/11 23:33:31 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_err(char *str)
{
	if (str)
	{
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd("malloc failed", STDERR);
}

int	syntax_err(char *line)
{
	ft_putendl_fd("syntax error", STDERR);
	free(line);
	return (-1);
}