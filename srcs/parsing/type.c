/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:06:50 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/27 13:04:11 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//verifier si le type est une redirection
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

//determiner le type
int	get_type(char *str, int	last_type)
{
	if (get_type_redir(str) != -1)
		return (REDIR);
	else if (str[0] == '|')
		return (PIPE);
	else if (last_type == REDIR)
		return (FILES);
	else if ((last_type == CMD) || last_type == ARG)
		return (ARG);
	else
		return (CMD);
}

//donner un type a chaque indice de la liste
void	type(t_list *list)
{
	int	last_type;

	last_type = -1;

	while (list)
	{
		// printf("(1)list content: %s, type: %i\n", list->content, list->type);
		// printf("(1)last_type: %i\n", last_type);
		if (last_type == REDIR || list->type == -1)
			list->type = get_type(list->content, last_type);
		// printf("(2)list content: %s, type: %i\n", list->content, list->type);
		last_type = list->type;
		// printf("(2)last_type: %i\n", last_type);
		list = list->next;
	}	
}
