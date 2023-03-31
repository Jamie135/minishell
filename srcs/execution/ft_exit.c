/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:50:49 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/16 13:50:59 by Espéranto        ###   ########.fr       */
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

void	ft_exit(char **arg)
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

// int	main(int ac, char **av)
// {
// 	char	**arg;

// 	arg = av;
// 	arg++;
// 	ft_exit(arg);
// 	while (1)
// 		;
// }
