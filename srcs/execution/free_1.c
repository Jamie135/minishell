/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:41:19 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/13 13:57:33 by pbureera         ###   ########.fr       */
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
		free_ptr((void **)&envi->cmd);
		free_ptr((void **)&envi->value);
		free_ptr((void **)&envi);
		envi = tmp;
	}
}