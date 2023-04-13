/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:53:52 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 17:24:04 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nombre(char *str)
{
	int	est_nombre;
	int	k;

	est_nombre = 1;
	if (!str[0])
		return (0);
	while (str[k])
	{
		if (!ft_isdigit(str[k]))
			est_nombre = 0;
		k++;
	}
	return (est_nombre);
}

void	do_exit(char **arg)
{
	int	statut;

	statut = 0;
	if (arg != NULL && arg[0] != NULL)
	{
		if (!nombre(arg[0]))
		{
			printf("l'argument de exit doit être un nombre\n");
		}
		else if (arg[1] != NULL)
		{
			printf("trop d'argument pour exit.\n");
			return ;
		}
		else
			statut = ft_atoi(arg[0]);
	}
	exit (statut);
}
