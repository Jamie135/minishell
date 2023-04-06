/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:44:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 16:28:53 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//set up les types de redirections 
int	type_redir(char *str, int type[2])
{
	if (ft_strcmp(str, ">\0") == 0)
	{
		type[OUTFILE]++;
		return (TRUNC);
	}
	else if (ft_strcmp(str, ">>\0") == 0)
	{
		type[OUTFILE]++;
		return (APPEND);
	}
	else if (ft_strcmp(str, "<\0") == 0 || ft_strcmp(str, "<<\0") == 0)
	{
		type[INFILE]++;
		return (TO_INFILE);
	}
	return (FAILURE);
}

int	no_cmd_list_redir(t_shell *shell, t_list *list, t_list **redir)
{
	t_list	*new_list;
	char	*name;
	int		type[2];
	int		i;
	
	i = 0;
	ft_bzero(type, sizeof(int) * 2);
	while (list && i <= shell->cmd_num)
	{
		if (list->type == REDIR && list->next && list->next->type == FILES)
		{
			name = list->next->content;
			new_list = ft_lstnew(name, type_redir(list->content, type));
			if (!new_list)
				return (EXIT_FAILURE);
			ft_lstadd_back(&redir[i], new_list);
		}
		valid_next(shell, list, type, &i);
		list = list->next;
	}
	return (EXIT_SUCCESS);
}

//creer une liste de redirections
int	list_redir(t_shell *shell, t_list *list)
{
	int	len;

	if (shell->redir_num == 0)
		return (EXIT_SUCCESS);
	if (shell->cmd_num == 0)
		shell->no_cmd = 1;
	len = shell->cmd_num + shell->no_cmd + 1;
	shell->redir == ft_calloc(sizeof(int), len);
	if (!shell->redir)
		return (EXIT_FAILURE);
	shell->infile = ft_calloc(sizeof(int), len);
	shell->outfile = ft_calloc(sizeof(int), len);
	if (!shell->outfile)
		return (EXIT_FAILURE);
	if (shell->no_cmd && no_cmd_list_redir(shell, list, shell->redir))
		return (EXIT_FAILURE);
	if (!shell->no_cmd && no_cmd_list_redir(shell, list, shell->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
