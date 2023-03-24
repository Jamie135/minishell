/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:45:53 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/24 16:18:58 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_num(t_list *list)
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
						expected_token(">");
					else
						expected_token("<");
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
