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

//executer les builtins echo, env, pwd ou export dans le child
int	builtins_child(t_shell *shell)
{
	if (!ft_strcmp(shell->args[shell->cid][0], "echo"))
		return (ft_echo(shell));
	else if (!ft_strcmp(shell->args[shell->cid][0], "env"))
		return (ft_env(shell));
	else if (!ft_strcmp(shell->args[shell->cid][0], "pwd"))
		return (ft_pwd(shell));
	else if (!ft_strcmp(shell->args[shell->cid][0], "export"))
		return (print_envi(shell, shell->envi), EXIT_SUCCESS);
	return (FAILURE);
}

//executer les builtins cd, export ou unset dans le parent
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
