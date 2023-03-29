/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:30:42 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 12:55:26 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//execution des commandes
t_envi	*execution(t_list *list, t_envi *env, int *count, int *exit_value)
{
	t_shell	*shell;
	t_envi	*envp;

	if (valid_num_redir(list) == -1 || valid_extra_token(list) == -1 \
		|| valid_after_redir(list) == -1 || valid_pipe(list) == -1)
	{
		*exit_value = 2;
		return (env);
	}
	if (heredoc(list, env, count, exit_value))
		return (free_list(list), env);
	if (expend_list(env, list, *exit_value))
		return (free_list(list), malloc_err("execution.c (1)"), env);
	shell = shell_struct(list, env, count, exit_value);
}
