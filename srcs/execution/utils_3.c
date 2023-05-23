/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:17:37 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/24 00:17:37 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins_after_pipe(t_shell *shell, t_list *list)
{
	while (list)
	{
		if (list->type == PIPE)
		{
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
