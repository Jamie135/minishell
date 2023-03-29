/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:07:21 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 17:09:44 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
