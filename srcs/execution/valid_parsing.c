/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:45:53 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/27 15:51:16 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_num_redir(t_list *list)
{
	const t_list	*tmp = list;
	int				i;

	while (list)
	{
		if (list->type == REDIR)
		{
			i = 0;
			while (list->content[i])
			{
				if (i > 1)
				{
					if (list->content[0] == '>')
						print_token(">");
					else
						print_token("<");
					free_list((t_list *)tmp);
					return (-1);
				}
				i++;
			}
		}
		list->next;
	}
	return (0);
}

//verifier si on a des tokens en trop
//ex: ">>>", "<<<", "||"
int	valid_extra_token(t_list *list)
{
	const t_list	*tmp = list;
	int				type;

	type = list->type;
	list = list->next;
	while (list)
	{
		if (list->type == type)
		{
			if (type == PIPE)
			{
				print_token(list->content);
				return (free_list((t_list *)tmp), -1);
			}
			if (type == REDIR)
			{
				print_token(list->content);
				return (free_list((t_list *)tmp), -1);
			}
		}
		type = list->type;
		list = list->next;
	}
	return (0);
}

//verifier qu'on a pas uniquement un \n apres les redirections
int	valid_after_redir(t_list *list)
{
	int				i;
	const t_list	*tmp = list;

	i = 0;
	while (list)
	{
		if (list->type == REDIR)
		{
			if (!list->next && (ft_strcmp(list->content, "<<") || i == 0))
			{
				print_token("newline");
				return (free_list((t_list *)tmp), -1);
			}
		}
		list = list->next;
		i++;
	}
	return (0);
}

//verifier si on a une mauvaise syntaxe des pipes
//ex: "|.", "|?", "!|"
int	valid_pipe(t_list *list)
{
	const t_list	*tmp = list;
	int				i;

	i = 0;
	while (list)
	{
		if (list->type == PIPE)
		{
			if (!list->next)
			{
				ft_putendl_fd("syntaxe error", STDERR);
				return (free_list((t_list *)tmp), -1);
			}
			if (i == 0)
			{
				print_token("|");
				return (free_list((t_list *)tmp), -1);
			}
		}
		list = list->next;
		i++;
	}
	return (0);
}
