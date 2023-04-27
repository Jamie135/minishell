/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:25:15 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/30 22:25:15 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parent_no_cmd(t_shell *shell)
{
	pid_t	*pid;

	pid = malloc(sizeof(*pid));
	if (pid == NULL)
		return (FAILURE);
	shell->pid = pid;
	*pid = fork();
	if (*pid == -1)
		return (FAILURE);
	if (*pid == 0)
	{
		parent_heredoc_signal(CHILD);
		child_no_cmd(shell);
	}
	waitpid(*pid, &shell->mode, WUNTRACED);
	pid_return(shell->mode);
	return (SUCCESS);
}

int	parent_one_cmd(t_shell *shell)
{
	if (builtins_parent(shell) == FAILURE)
	{
		shell->pid[0] = fork();
		if (shell->pid[0] == -1)
			return (FAILURE);
		if (shell->pid[0] == 0)
		{
			parent_heredoc_signal(CHILD);
			child_cmd_1(shell);
		}
	}
	waitpid(shell->pid[0], &shell->mode, WUNTRACED);
	if (shell->mode == 2)
		shell->mode = 130;
	pid_return(shell->mode);
	return (SUCCESS);
}

int	parent_n_cmd(t_shell *shell)
{
	int	i;

	while (shell->cid < shell->cmd_num)
	{
		if (builtins_parent(shell) == FAILURE)
		{
			shell->pid[shell->cid] = fork();
			if (shell->pid[shell->cid] == -1)
				return (FAILURE);
			if (shell->pid[shell->cid] == 0)
			{
				parent_heredoc_signal(CHILD);
				child_n_cmd(shell);
			}
		}
		shell->cid++;
	}
	close_pipes(shell->pipes, shell->cmd_num - 1);
	i = 0;
	while (i < shell->cmd_num)
		waitpid(shell->pid[i++], &shell->mode, 0);
	return (SUCCESS);
}

int	parent_one_cmd_redir(t_shell *shell)
{
	if (builtins_parent(shell) == FAILURE)
	{
		shell->pid[0] = fork();
		if (shell->pid[0] == -1)
			return (FAILURE);
		if (shell->pid[0] == 0)
		{
			parent_heredoc_signal(CHILD);
			child_cmd_redir(shell);
		}
	}
	waitpid(shell->pid[0], &shell->mode, 0);
	return (SUCCESS);
}

int	parent_n_cmd_redir(t_shell *shell)
{
	int	i;

	while (shell->cid < shell->cmd_num)
	{
		if (builtins_parent(shell) == FAILURE)
		{
			shell->pid[shell->cid] = fork();
			if (shell->pid[shell->cid] == -1)
				return (FAILURE);
			if (shell->pid[shell->cid] == 0)
			{
				parent_heredoc_signal(CHILD);
				child_n_cmd_redir(shell);
			}
		}
		shell->cid++;
	}
	close_pipes(shell->pipes, shell->cmd_num - 1);
	i = 0;
	while (i < shell->cmd_num)
		waitpid(shell->pid[i++], &shell->mode, 0);
	return (SUCCESS);
}
