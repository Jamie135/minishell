/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:33:31 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/27 17:20:11 by pbureera         ###   ########.fr       */
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

void	print_token(char *str)
{
	ft_putstr_fd(SYNTAX_ERR, STDERR);
	ft_putstr_fd(" `", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putendl_fd("\'", STDERR);	
}

void	message_heredoc(t_heredoc *heredoc, char *str, int n, void (*f)(int))
{
	if (n > 0 && str)
		perror(str);
	else if (n > 0)
		ft_putendl_fd(strerror(errno), STDERR);
	if (!f && heredoc)
		free_heredoc(heredoc, NULL, NULL, -1);
	if (f)
	{
		if (heredoc)
			free_heredoc(heredoc, NULL, NULL, -1);
		f(n);
	}
}
