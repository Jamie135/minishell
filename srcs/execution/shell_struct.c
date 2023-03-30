/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:52:46 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 16:33:27 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipes(t_shell *shell)
{
	int		**pipes;
	int		i;

	pipes = NULL;
	if (shell->cmd_num == 1)
		return (NULL);
	pipes = (int **)ft_calloc(sizeof(int *), (shell->cmd_num - 1));
	if (!pipes)
		return (message_free_exit(shell, "shell_struct.c (8)", MALLOC, NULL), ERROR);
	i = -1;
}

char	***init_args(t_shell *shell, t_list *list)
{
	char	***args;
	int		i;
	int		len;

	args = NULL;
	args = (char ***)ft_calloc(sizeof(char **), (shell->cmd_num + 1));
	if (!args)
		return (message_free_exit(shell, "shell_struct.c (6)", MALLOC, NULL), NULL);
	i = 0;
	while (i < shell->cmd_num)
	{
		args[i] = list_args(list);
		if (!args[i])
			return (free_args(args, i), \
					message_free_exit(shell, "shell_struct.c (7)", MALLOC, NULL), NULL);
		while (list && list->type != CMD)
			list = list->next;
		len = len_args(list) + 1;
		while (list && len--)
			list = list->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

pid_t	init_pid(t_shell *shell)
{
	pid_t	*pid;
	int		i;

	pid = NULL;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), shell->cmd_num);
	if (!pid)
		return (message_free_exit(shell, "shell_struct.c (5)", MALLOC, NULL), NULL);
	i = 0;
	while (i < shell->cmd_num)
	{
		pid[i] = 0;
		i++;
	}
	return (pid);
}

int	shell_process(t_shell *shell, t_list *list)
{
	shell->pid = init_pid(shell);
	if (!shell->pid)
		return (FAILURE);
	shell->args = init_args(shell, list);
	if (!shell->args)
		return (FAILURE);
	shell->pipes = init_pipes(shell);
	if (shell->pipes == ERROR)
		return (FAILURE);
	return (SUCCESS);
}

t_shell	*shell_struct(t_list *list, t_envi *envi, int *count, int *exit_value)
{
	t_shell	*shell;

	shell = NULL;
	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (malloc_err("shell_struct.c (1)"), NULL);
	shell->list = list;
	shell->environment = init_env(envi);
	if (shell->environment == FAILURE)
		return (message_free_exit(shell, "shell_struct.c (2)", MALLOC, NULL), NULL);
	shell->envi = envi;
	shell->line_num = count;
	shell->exit_value = exit_value;
	shell->cmd_num = num_command(list);
	shell->redir_num = num_redir(list);
	if (list_redir(shell, list))
		return (message_free_exit(shell, "shell_struct.c (3)", MALLOC, NULL), NULL);
	if (!shell->redir && shell->redir_num > 0)
		return (message_free_exit(shell, "shell_struct.c (4)", MALLOC, NULL), NULL);
	if (shell->cmd_num > 0 && shell_process(shell, list) == FAILURE)
		return (NULL);
	return (shell);
}
