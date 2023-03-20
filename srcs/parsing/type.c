/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:06:50 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 16:18:44 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_type_redir(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (REDIR);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (REDIR);
	return (-1);
}

int	get_type(char *str, int	last_type)
{
	if (get_type_redir(str) != 1)
		return (REDIR);
	else if (str[0] == '|')
		return (PIPE);
	else if (last_type == REDIR)
		return (FILES);
	else if (last_type == CMD || last_type == ARG)
		return (ARG);
	else
		return (CMD);
}

void	type(t_list *list)
{
	int	last_type;

	last_type = -1;
	while (list)
	{
		if (last_type == REDIR || list->type == -1)
			list->type = get_type(list->content, last_type);
		last_type = list->type;
		list = list->next;
	}	
}
