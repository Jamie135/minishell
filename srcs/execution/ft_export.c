/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:56:08 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/16 13:56:13 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*apres_egal(const char *str)
{
	return (value_env((char *)str));
}

static char	*avant_egal(const char *str)
{
	return (variable_env((char *)str));
}

static void	liste_complete(t_envi *envi)
{
	t_envi	*parcours;

	parcours = envi;
	while (parcours)
	{
		printf("declare -x ");
		printf("%s=%s\n", parcours->ve, parcours->value);
		parcours = parcours->next;
	}
}

// ajoute une nouvelle variable d'environement a la fin de la liste chainee.
static void	ajoute(const char *str, t_envi *envi)
{
	while (envi->next)
		envi = envi->next;
	envi->ve = avant_egal(str);
	envi->value = apres_egal(str);
	envi->next = NULL;
}

int	ft_export(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	int			k;
	int			trouvee;
	t_envi		*parcours;

	k = 0;
	if (!arg || !arg[0])
	{
		liste_complete(shell->envi);
		return (FAILURE);
	}
	while (arg[k])
	{
		trouvee = 0;
		parcours = shell->envi;
		while (parcours)
		{
			if (identique(parcours->ve, avant_egal(arg[k])))
			{
				parcours->value = apres_egal(arg[k]);
				trouvee = 1;
			}
		parcours = parcours->next;
		}
		if (!trouvee)
			ajoute(arg[k], shell->envi);
		k++;
	}
	return (EXIT_SUCCESS);
}