/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:27:00 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/15 14:27:12 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	int			erreur;

	arg++;
	if (!arg || !arg[0])
	{
		chdir("~");
		return (EXIT_FAILURE);
	}
	if (arg[1])
	{
		printf("cd: ERREUR trop d'arguments\n");
		return (EXIT_FAILURE);
	}
	erreur = chdir(arg[0]);
	if (erreur == -1)
		printf("cd: ERREUR entrez un chemin relatif ou absolu valide\n");
	return (EXIT_SUCCESS);
}
