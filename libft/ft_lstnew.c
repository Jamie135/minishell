/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:54:38 by pbureera          #+#    #+#             */
/*   Updated: 2022/06/14 14:19:27 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

t_list	*ft_lstnew(char *content, int type)
{
	t_list	*contenu;

	contenu = malloc(sizeof(*contenu));
	if (!contenu)
		return (NULL);
	contenu->content = content;
	contenu->type = type;
	contenu->next = NULL;
	return (contenu);
}
