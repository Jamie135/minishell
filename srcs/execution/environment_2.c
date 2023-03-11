/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:23:09 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/11 23:23:09 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envi	*get_last_envi(t_envi *envi)
{
	if (!envi)
		return (NULL);
	while (envi && envi->next)
		envi = envi->next;
	return (envi);
}