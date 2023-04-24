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

#include "../../includes/minishell.h"

int	identique(char *str1, const char *str2)
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

// int	ft_unset(t_shell *shell)
// {
// 	const char	**arg = (const char **)shell->args[shell->cid];
// 	int		k;
// 	t_envi	*parcours;

// 	arg++;
// 	k = 0;
// 	if (!arg || !arg[0])
// 	{
// 		printf("unset: trop peu d'arguments\n");
// 		return (EXIT_FAILURE);
// 	}
// 	while (arg[k])
// 	{
// 		parcours = shell->envi;
// 		while (parcours)
// 		{
// 			if (identique(parcours->ve, arg[k]))
// 				parcours->value[0] = '\0';
// 			parcours = parcours->next;
// 		}
// 		k++;
// 	}
// 	return (EXIT_SUCCESS);
// }

static t_envi	*free_unset(t_envi *envi, t_envi *tmp, t_envi *new_envi)
{
	if (tmp == NULL)
	{
		tmp = envi;
		envi = envi->next;
		free_one_envi(tmp);
		return (envi);
	}
	else if (tmp && envi->next == NULL)
	{
		tmp->next = NULL;
		free_one_envi(envi);
		return (new_envi);
	}
	else
	{
		tmp->next = envi->next;
		free_one_envi(envi);
		return (new_envi);
	}
	return (new_envi);
}

static t_envi	*do_unset(const char *str, t_envi *envi)
{
	t_envi	*tmp;
	t_envi	*new_envi;

	tmp = NULL;
	new_envi = envi;
	while (envi)
	{
		if (ft_strcmp(str, "_") == 0)
			return (new_envi);
		else if (ft_strcmp(str, envi->ve) == 0)
			return (free_unset(envi, tmp, new_envi));
		tmp = envi;
		envi = envi->next;
	}
	return (new_envi);
}

int	ft_unset(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	int			k;

	if (arg[1] == NULL)
		return (EXIT_SUCCESS);
	free_split(shell->environment);
	k = 0;
	while (arg[k])
		shell->envi = do_unset(arg[k++], shell->envi);
	shell->environment = init_env(shell->envi);
	if (shell->environment == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
