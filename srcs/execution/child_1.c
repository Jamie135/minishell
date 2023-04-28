/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:51:54 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 17:16:48 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_no_cmd(t_shell *shell)
{
	const int	id = shell->cid;
	int			infile;
	int			outfile;

	infile = -1;
	outfile = -1;
	infile = open_infile(shell, shell->redir[id]);
	close_fd(&infile);
	outfile = open_outfile(shell, shell->redir[id]);
	close_fd(&outfile);
	free_shell_1(shell);
	exit(EXIT_SUCCESS);
}

void	child_cmd_2(t_shell *shell, const int id)
{
	char	*tmp;
	char	*cmd;
	char	**path;

	path = get_path(shell);
	tmp = ft_strjoin("/", shell->args[id][0]);
	if (!tmp)
		return (free_split(path), \
				msgexit(shell, NULL, MALLOC, &exit));
	cmd = get_access(tmp, path);
	if (!cmd)
		return (free_split(path), free(tmp), \
				msgexit(shell, NULL, MALLOC, &exit));
	if (cmd == ERROR && !ft_strcmp("exit", shell->args[id][0]))
		return (free_split(path), free(tmp), \
				msgexit(shell, shell->args[id][0], EXIT, &exit));
	if (cmd == ERROR)
		return (free_split(path), free(tmp), \
				msgexit(shell, shell->args[id][0], COMMAND, &exit));
	free(tmp);
	execve(cmd, shell->args[id], shell->environment);
	free_child(shell, path, cmd);
	exit(EXIT_FAILURE);
}

void	child_cmd_1(t_shell *shell)
{
	const int	id = shell->cid;

	if (builtins_child(shell) != FAILURE)
		return (msgexit(shell, NULL, 0, &exit));
	if ((ft_strncmp("./", shell->args[id][0], 2) == 0 && \
		access(shell->args[id][0], X_OK) != FAILURE) || \
		ft_strchr(shell->args[id][0], '/') != NULL)
	{
		execve(shell->args[id][0], shell->args[id], shell->environment);
		msgexit(shell, shell->args[id][0], errno, &exit);
	}
	child_cmd_2(shell, id);
}

void	child_n_cmd(t_shell *shell)
{
	if (shell->cid == 0)
	{
		if (dup2(shell->pipes[shell->cid][1], STDOUT) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[shell->cid][0]);
	}
	else if (shell->cid == shell->cmd_num - 1)
	{
		if (dup2(shell->pipes[shell->cid - 1][0], STDIN) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[shell->cid - 1][1]);
	}
	else
	{
		if (dup2(shell->pipes[shell->cid - 1][0], STDIN) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[shell->cid - 1][1]);
		if (dup2(shell->pipes[shell->cid][1], STDOUT) == FAILURE)
			return (msgexit(shell, NULL, errno, &exit));
		close_fd(&shell->pipes[shell->cid][0]);
	}
	close_pipes(shell->pipes, shell->cmd_num - 1);
	child_cmd_1(shell);
}

void	child_cmd_redir(t_shell *shell)
{
	const int	id = shell->cid;
	int			infile;
	int			outfile;

	if (shell->infile[id])
	{
		infile = open_infile(shell, shell->redir[id]);
		if (dup2(infile, STDIN) == FAILURE)
			return (close(infile), free_shell_1(shell), exit(EXIT_FAILURE));
		close_fd(&infile);
	}
	if (shell->outfile[id])
	{
		outfile = open_outfile(shell, shell->redir[id]);
		if (dup2(outfile, STDOUT) == FAILURE)
			return (close(outfile), free_shell_1(shell), exit(EXIT_FAILURE));
		close_fd(&outfile);
	}
	child_cmd_1(shell);
}
