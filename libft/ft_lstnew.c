/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:54:38 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 16:01:12 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

t_list	*ft_lstnew_2(char *content, int type, bool unexpended, bool quoted)
{
	t_list	*contenu;

	(void)quoted;
	contenu = ft_calloc(sizeof(*contenu), 1);
	if (!contenu)
		return (NULL);
	contenu->unexpended = unexpended;
	contenu->content = content;
	contenu->type = type;
	if (quoted == true)
		contenu->type = ARG;
	contenu->next = NULL;
	return (contenu);
}
