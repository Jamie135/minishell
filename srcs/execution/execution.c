/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:30:42 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/24 16:39:46 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//execution des commandes
t_envi	*execution(t_list *list, t_envi *env, int *count, int *exit_value)
{
	t_shell	*shell;
	t_envi	*envp;

	if (valid_redir_num(list) == -1 || valid_arrow_pipe(list) == -1 \
		|| valid_next_arrow(list) == -1 || valid_pipe(list) == -1)
	{
		*exit_value = 2;
		return (env);
	}
}