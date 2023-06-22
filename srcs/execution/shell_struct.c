/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:52:46 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 17:21:37 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//creer une liste de liste d'entier qu'on va pipe() a chaque indice i
int	**init_pipes(t_shell *shell)
{
	int		**pipes;
	int		i;

	pipes = NULL;
	if (shell->cmd_num == 1)
		return (NULL);
	pipes = (int **)ft_calloc(sizeof(int *), (shell->cmd_num - 1));
	if (!pipes)
		return (msgexit(shell, "shell_struct.c (8)", MALLOC, NULL), ERROR);
	i = -1;
	while (++i < shell->cmd_num - 1)
	{
		pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!pipes[i])
			return (free_pipes(pipes, (int)i), \
					close_pipes(pipes, shell->cmd_num - 1), \
					msgexit(shell, "shell_struct.c (9)", MALLOC, NULL), ERROR);
	}
	i = -1;
	while (++i < shell->cmd_num - 1)
		if (pipe(pipes[i]) == -1)
			return (close_pipes(pipes, shell->cmd_num - 1), \
					msgexit(shell, "pipes: ", errno, NULL), ERROR);
	return (pipes);
}

//creer une liste d'arguments de char **
char	***init_args(t_shell *shell, t_list *list)
{
	char	***args;
	int		i;
	int		len;

	args = NULL;
	args = (char ***)ft_calloc(sizeof(char **), (shell->cmd_num + 1));
	if (!args)
		return (msgexit(shell, "shell_struct.c (6)", MALLOC, NULL), NULL);
	i = 0;
	while (i < shell->cmd_num)
	{
		args[i] = list_args(list);
		if (!args[i])
			return (free_args(args, i), \
					msgexit(shell, "shell_struct.c (7)", MALLOC, NULL), NULL);
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

// int j = 0;
// while (j < len_array((char **)args[i]))
// {
// 	printf("args[%i][%i]: %s\n", i, j, args[i][j]);
// 	j++;
// }

//creer un array de pid ou chaque indice est initialise a 0
pid_t	*init_pid(t_shell *shell)
{
	pid_t	*pid;
	int		i;

	pid = NULL;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), shell->cmd_num);
	if (!pid)
		return (msgexit(shell, "shell_struct.c (5)", MALLOC, NULL), NULL);
	i = 0;
	while (i < shell->cmd_num)
	{
		pid[i] = 0;
		i++;
	}
	return (pid);
}

//initialiser la struct de shell
int	init_shell(t_shell *shell, t_list *list)
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

// printf("content: %s, type: %i\n", content, type);
// printf("next content: %s, type: %i\n", next content, next type);

//initialiser la struct de shell
t_shell	*shell_struct(t_list *list, t_envi *envi, int *count, int *exit_value)
{
	t_shell	*shell;

	shell = NULL;
	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (malloc_err("shell_struct.c (1)"), NULL);
	shell->list = list;
	builtins_after_pipe(shell, list);
	shell->environment = init_env(envi);
	if (shell->environment == ERROR)
		return (msgexit(shell, "shell_struct.c (2)", MALLOC, NULL), NULL);
	shell->envi = envi;
	shell->line_num = count;
	shell->exit_value = exit_value;
	shell->cmd_num = num_command(list);
	shell->redir_num = num_redir(list);
	if (list->heredoc)
		shell->heredoc = 1;
	if (list_redir(shell, list))
		return (msgexit(shell, "shell_struct.c (3)", MALLOC, NULL), NULL);
	if (!shell->redir && shell->redir_num > 0)
		return (msgexit(shell, "shell_struct.c (4)", MALLOC, NULL), NULL);
	if (shell->cmd_num > 0 && init_shell(shell, list) == FAILURE)
		return (NULL);
	return (shell);
}
