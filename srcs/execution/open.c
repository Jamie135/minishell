/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:56:06 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/30 23:56:06 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *name, t_redir type)
{
	if (type == TO_INFILE)
		return (open(name, O_RDONLY));
	else if (type == TO_OUTFILE)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (FAILURE);
}

int	open_infile(t_shell *shell, t_list *redir)
{
	int	fd;

	fd = -2;
	while (redir)
	{
		if (redir->type == TO_INFILE || redir->type == HEREDOC)
			close_fd(&fd);
		if (redir->type == TO_INFILE)
		{
			fd = open_file(redir->content, TO_INFILE);
			if (fd == -1)
				return (message_free_exit(shell, redir->content, errno, &exit), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

int	open_outfile(t_shell *shell, t_list *redir)
{
	int	fd;

	fd = -2;
	while (redir)
	{
		if (redir->type == TO_OUTFILE || redir->type == APPEND)
			close_fd(&fd);
		if (redir->type == TO_OUTFILE)
		{
			fd = open_file(redir->content, TO_OUTFILE);
			if (fd == -1)
				return (message_free_exit(shell, redir->content, errno, &exit), FAILURE);
		}
		else if (redir->type == APPEND)
		{
			fd = open_file(redir->content, APPEND);
			if (fd == -1)
				return (message_free_exit(shell, redir->content, errno, &exit), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}
