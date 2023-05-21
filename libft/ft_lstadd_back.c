/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:29:21 by pbureera          #+#    #+#             */
/*   Updated: 2022/06/14 14:35:47 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*in;

	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			in = ft_lstlast(*lst);
			in->next = new;
		}
		else
			*lst = new;
	}
}
