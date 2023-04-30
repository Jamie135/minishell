/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:30:50 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 17:31:48 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_inexistance(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -2)
			return (-1);
		i++;
	}
	return (0);
}

void	ajoute(const char *str, t_envi *envi)
{
	while (envi->next)
		envi = envi->next;
	envi->ve = variable_env((char *)str);
	envi->value = value_env((char *)str);
	envi->next = NULL;
}

void	met_a_jour_oldpwd(t_shell *shell, char *ancien_chemin)
{
	int			trouvee;
	const char	**arg = (const char **)shell->args[shell->cid];
	t_envi		*parcours;

	trouvee = 0;
	parcours = shell->envi;
	while (parcours)
	{
		if (identique(parcours->ve, "OLDPWD"))
		{
			parcours->value = ancien_chemin;
			trouvee = 1;
		}
		parcours = parcours->next;
	}
}
