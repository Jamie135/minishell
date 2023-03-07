/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:53:50 by pbureera          #+#    #+#             */
/*   Updated: 2022/06/14 15:13:18 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmpptr;
	t_list	*newlist;

	newlist = malloc(sizeof(*newlist));
	if (!lst || !newlist || !del || !(*f))
		return (NULL);
	tmpptr = newlist;
	while (lst)
	{
		tmpptr->content = (*f)(lst->content);
		if (lst->next)
		{
			tmpptr->next = malloc(sizeof(*tmpptr));
			if (tmpptr->next == NULL)
			{
				ft_lstdelone(newlist, (*del));
				return (NULL);
			}
		}
		lst = lst->next;
		if (lst)
			tmpptr = tmpptr ->next;
	}
	tmpptr->next = NULL;
	return (newlist);
}
