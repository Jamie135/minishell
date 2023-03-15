/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:41:19 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 17:16:38 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ptr(void **ptr)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_envi(t_envi *envi)
{
	t_envi	*tmp;

	while (envi)
	{
		tmp = envi->next;
		free_ptr((void **)&envi->ve);
		free_ptr((void **)&envi->value);
		free_ptr((void **)&envi);
		envi = tmp;
	}
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free_ptr((void **)&list->content);
		free_ptr((void **)&list);
		list = tmp;
	}
}

void	free_split(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free_ptr((void **)&tab[i]);
		i++;
	}
	free_ptr((void **)&tab);
}