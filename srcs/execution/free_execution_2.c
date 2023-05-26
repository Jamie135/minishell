/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:04:23 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/26 14:35:13 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_one_envi(t_envi *envi)
{
	free_ptr((void **)&envi->ve);
	free_ptr((void **)&envi->value);
	free_ptr((void **)&envi);
}

void	free_n_split(char **split, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free_ptr((void **)&split[i]);
		i++;
	}
	free(split);
}

static void	free_shell_2(t_shell *shell)
{
	if (shell->redir)
	{
		if (shell->right || (shell->left && shell->right && shell->pipe))
			free_redir(shell->redir, shell->cmd_num + shell->no_cmd);
		else
			free_redir(shell->redir, shell->cmd_num + shell->no_cmd + 1);
		shell->redir = NULL;
	}
	if (shell->pid)
		free_ptr((void **)&shell->pid);
	if (shell->pipes)
	{
		free_pipes(shell->pipes, (shell->cmd_num - 1));
		shell->pipes = NULL;
	}
	if (shell->args)
	{
		free_args(shell->args, shell->cmd_num);
		shell->args = NULL;
	}
}

// int	i = 0;
// while (i < shell->cmd_num + shell->no_cmd + 1)
// {
// 	while (shell->redir[i])
// 	{
// 		printf("redir[%i]: %s\n", i, shell->redir[i]->content);
// 		shell->redir[i] = shell->redir[i]->next;
// 	}
// 	i++;
// }

void	free_shell_1(t_shell *shell)
{
	if (shell->list)
	{
		free_list(shell->list);
		shell->list = NULL;
	}
	if (shell->environment)
	{
		free_split(shell->environment);
		shell->environment = NULL;
	}
	if (shell->envi)
	{
		free_envi(shell->envi);
		shell->envi = NULL;
	}
	if (shell->infile)
		free_ptr((void **)&shell->infile);
	if (shell->outfile)
		free_ptr((void **)&shell->outfile);
	free_shell_2(shell);
	free_ptr((void **)&shell);
}
