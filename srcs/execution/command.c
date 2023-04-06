/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:07:21 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 15:26:17 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//compter le nombre de redirection dans la liste
size_t	num_redir(t_list *list)
{
	size_t	num;

	num = 0;
	while (list)
	{
		if (list->type == REDIR)
			num++;
		list = list->next;
	}
	return (num);
}

//compter le nombre de commande dans la liste
size_t	num_command(t_list *list)
{
	size_t	num;

	num = 0;
	while (list)
	{
		if (list->type == CMD)
			num++;
		list = list->next;
	}
	return (num);
}
