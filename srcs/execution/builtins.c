/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:39:31 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/31 23:39:31 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins_parent(t_shell *shell)
{
	if (!ft_strcmp(shell->args[shell->cid][0], "cd"))
	{
		shell->mode = ft_cd(shell);
		return (shell->mode);
	}
	else if (!ft_strcmp(shell->args[shell->cid][0], "export"))
	{
		shell->mode = ft_export(shell);
		if (shell->mode == FAILURE)
		{
			shell->mode = 0;
			return (FAILURE);
		}
		return (shell->mode);
	}
	else if (!ft_strcmp(shell->args[shell->cid][0], "unset"))
	{
		shell->mode = ft_unset(shell);
		return (shell->mode);
	}
	return (FAILURE);
}
