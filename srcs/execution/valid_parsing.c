/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:45:53 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/26 16:50:13 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extra_token(t_list *list, int type, char *tmp)
{
	if (list->type == type)
	{
		if (type == PIPE)
		{
			if (!ft_strcmp(tmp, "|"))
			{
				print_token("||");
				return (-1);
			}
			print_token(list->content);
			return (-1);
		}
		if (type == REDIR)
		{
			print_token(list->content);
			return (-1);
		}
	}
	return (0);
}

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
		list = list->next;
	}
	return (0);
}

//verifier si on a des tokens en trop
//ex: ">>>", "<<<", "||"
int	valid_extra_token(t_list *list)
{
	const t_list	*tmp = list;
	char			*tmp_content;
	int				type;

	tmp_content = list->content;
	type = list->type;
	list = list->next;
	while (list)
	{
		if (extra_token(list, type, tmp_content) == -1)
			return (free_list((t_list *)tmp), -1);
		type = list->type;
		list = list->next;
	}
	return (0);
}

// if (list)
// 	{
// 		if (!ft_strcmp(list->content, "<") && !is_command(tmp_content))
// 		{
// 			if (extra_redir(tmp_content) == -1)
// 				return (free_list((t_list *)tmp), -1);
// 			print_token(tmp_content);
// 			return (free_list((t_list *)tmp), -1);
// 		}
// 	}

// while (list && list->next)
// {
// 	printf("content: %s ; ", list->content);
// 	printf("type: %i\n", list->type);
// 	list = list->next;
// }

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
