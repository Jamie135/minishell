/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:09:34 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/28 22:09:34 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//retourner la valeur du variable environnement de envi
char	*find_value_envi(char *name, t_envi *envi)
{
	if (!envi)
		return (NULL);
	while (envi)
	{
		if (ft_strcmp(envi->ve, name) === 0)
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}
