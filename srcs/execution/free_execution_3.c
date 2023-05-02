/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:10:41 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/02 16:24:59 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_child(t_shell *shell, char **path, char *cmd)
{
	if (shell)
		free_shell_1(shell);
	if (path)
		free_split(path);
	if (cmd)
		free(cmd);
}

void	free_redir(t_list **list, int n)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (i < n)
	{
		while (list[i])
		{
			tmp = list[i]->next;
			free_ptr((void **)&list[i]);
			list[i] = tmp;
		}
		i++;
	}
	free(list);
}

// printf("content: %s\n", list[i]->content);

void	free_pipes(int **pipes, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free_ptr((void **)&pipes[i]);
		i++;
	}
	free_ptr((void **)&pipes);
}

void	free_args(char ***args, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free_split(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

void	free_one_list(t_list **list, t_list *lst)
{
	t_list	*next;

	next = (*list)->next;
	if (ft_strcmp(lst->content, "echo"))
		ft_lst_print_type(next);
	free_ptr((void **)&(*list)->content);
	free_ptr((void **)list);
	(*list) = lst;
	if (next)
		(*list)->next = next;
	else
		(*list)->next = NULL;
}

// while (lst && lst->next)
// {
// 	printf("list content: %s ; ", lst->content);
// 	printf("type: %i\n", lst->type);
// 	lst = lst->next;
// }
