/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:40:11 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 17:16:35 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ouvrir infile et outfile dans le pipe
static void	child_pipe_in_out(t_shell *shell)
{
	const int	id = shell->cid;
	int			infile;
	int			outfile;

	infile = open_infile(shell, shell->redir[id]);
	if (dup2(infile, STDIN) == FAILURE)
		return (close(infile), free_shell_1(shell), exit(EXIT_FAILURE));
	close_fd(&infile);
	outfile = open_outfile(shell, shell->redir[id]);
	if (dup2(outfile, STDOUT) == FAILURE)
		return (close(outfile), free_shell_1(shell), exit(EXIT_FAILURE));
	close_fd(&outfile);
}

//ouvrir infile dans le pipe
static void	child_pipe_in(t_shell *shell)
{
	const int	id = shell->cid;
	int			infile;

	infile = open_infile(shell, shell->redir[id]);
	if (dup2(infile, STDIN) == FAILURE)
		return (close(infile), msgexit(shell, NULL, errno, &exit));
	close_fd(&infile);
	if (id < shell->cmd_num - 1)
	{
		if (dup2(shell->pipes[id][1], STDOUT) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[id][1]);
	}
}

//ouvrir outfile dans le pipe
static void	child_pipe_out(t_shell *shell)
{
	const int	id = shell->cid;
	int			outfile;

	if (id > 0)
	{
		if (dup2(shell->pipes[id - 1][0], STDIN) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[id - 1][0]);
	}
	outfile = open_outfile(shell, shell->redir[id]);
	if (dup2(outfile, STDOUT) == FAILURE)
		return (close(outfile), msgexit(shell, NULL, errno, &exit));
	close_fd(&outfile);
}

//
static void	child_pipe_dup(t_shell *shell)
{
	const int	id = shell->cid;

	if (id == 0)
	{
		if (dup2(shell->pipes[id][1], STDOUT) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[id][0]);
	}
	else if (id == shell->cmd_num - 1)
	{
		if (dup2(shell->pipes[id - 1][0], STDIN) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[id - 1][1]);
	}
	else
	{
		if (dup2(shell->pipes[id - 1][0], STDIN) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[id - 1][1]);
		if (dup2(shell->pipes[id][1], STDOUT) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[id][0]);
	}
}

void	child_n_cmd_redir(t_shell *shell)
{
	const int	id = shell->cid;

	if (shell->infile[id] && shell->outfile[id])
		child_pipe_in_out(shell);
	else if (shell->infile[id] && !shell->outfile[id])
		child_pipe_in(shell);
	else if (!shell->infile[id] && shell->outfile[id])
		child_pipe_out(shell);
	else
		child_pipe_dup(shell);
	close_pipes(shell->pipes, shell->cmd_num - 1);
	child_cmd_1(shell);
}
