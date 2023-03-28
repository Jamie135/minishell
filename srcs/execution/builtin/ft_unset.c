/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:58:05 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/16 13:58:09 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	identique(char *str1, char *str2)
{
	int	k;

	k = 0;
	while (str1[k] && str2[k])
	{
		if (str1[k] != str2[k])
			return (0);
		k++;
	}
	if (str1[k] != str2[k])
		return (0);
	return (1);
}

void	ft_unset(t_envi *envi, char **arg)
{
	int		k;
	t_envi	*parcours;

	k = 0;
	if (!arg || !arg[0])
	{
		printf("unset: trop peu d'arguments");
		return ;
	}
	while (arg[k])
	{
		parcours = envi;
		while (parcours)
		{
			if (identique(parcours->ve, arg[k]))
				parcours->value = "";
			parcours = parcours->next;
		}
		k++;
	}
}