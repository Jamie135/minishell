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
		//init_signal(CHILD);
		child_no_cmd(shell);
	}
	waitpid(*pid, &shell->mode, WUNTRACED);
	pid_return(shell->mode);
	return (SUCCESS);
}

int	parent_one_cmd(t_shell *shell)
{
	
}
