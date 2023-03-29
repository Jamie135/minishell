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
}
