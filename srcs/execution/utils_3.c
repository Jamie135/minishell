/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:17:37 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/26 14:55:10 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd_go_to_2(t_shell *shell, char *oldpwd, char *pwd, int flag)
{
	if (!pwd)
		return (free(oldpwd), msgexit(NULL, "cd", errno, NULL), 1);
	if (ft_cd_update_oldpwd(shell, oldpwd, flag))
		return (free(pwd), EXIT_FAILURE);
	if (ft_cd_update_pwd(shell, pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd_back_2(t_shell *shell, char *oldpwd, char *pwd, int flag)
{
	if (ft_cd_update_oldpwd(shell, oldpwd, flag))
		return (EXIT_FAILURE);
	if (ft_cd_update_pwd(shell, pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	builtins_after_pipe(t_shell *shell, t_list *list)
{
	while (list)
	{
		if (list->type == REDIR)
		{
			if (!ft_strcmp(list->content, "<"))
				shell->left = 1;
			if (!ft_strcmp(list->content, ">") \
				|| !ft_strcmp(list->content, ">>"))
				shell->right = 1;
		}
		if (list->type == PIPE)
		{
			shell->pipe = 1;
			if (!ft_strcmp(list->next->content, "export") \
				|| !ft_strcmp(list->next->content, "cd") \
				|| !ft_strcmp(list->next->content, "exit") \
				|| !ft_strcmp(list->next->content, "unset"))
				shell->ignore = 1;
		}
		list = list->next;
	}
}

// while (shell->list)
// 	{
// 		printf("list content: %s\n", shell->list->content);
// 		shell->list = shell->list->next;
// 	}
