/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:32:53 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/08 00:32:53 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd(t_list **list, t_list *new_list)
{
	t_list	*last;
	t_list	*tmp;

	tmp = NULL;
	if ((*list)->next && (*list)->next->next)
		tmp = (*list)->next->next;
	(*list)->next = new_list;
	last = ft_lstlast(new_list);
	last->next = tmp;
}
