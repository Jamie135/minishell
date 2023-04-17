/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:23:09 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/13 15:52:04 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//retourner la derniere struct de la liste envi
t_envi	*get_last_envi(t_envi *envi)
{
	if (!envi)
		return (NULL);
	while (envi && envi->next)
		envi = envi->next;
	return (envi);
}

//ajouter le ve PWD a envi
static int	pwd_envi(t_envi **envi)
{
	char	*cmd;
	char	*value;
	t_envi	*cpy;
	
	cmd = ft_strdup("PWD");
	if (!cmd)
		return (EXIT_FAILURE);
	value = getcwd(NULL, 0);
	if (!value)
		return (free(cmd), EXIT_FAILURE);
	cpy = cpy_struct_envi(cmd, value, VALID);
	if (!cpy)
		return (free(cmd), free(value), EXIT_FAILURE);
	add_back_envi(envi, cpy);
	return (EXIT_SUCCESS);
}

//ajouter le ve SHLVL a envi
static int	shlvl_envi(t_envi **envi)
{
	char	*cmd;
	char	*value;
	t_envi	*cpy;

	cmd = ft_strdup("SHLVL");
	if (!cmd)
		return (EXIT_FAILURE);
	value = ft_strdup("0");
	if (!value)
		return (free(cmd), EXIT_FAILURE);
	cpy = cpy_struct_envi(cmd, value, VALID);
	if (!cpy)
		return (free(cmd), free(value), EXIT_FAILURE);
	add_back_envi(envi, cpy);
	return (EXIT_SUCCESS);
}

//ajouter _ a envi
static int	underscore_envi(t_envi **envi)
{
	char	*cmd;
	char	*value;
	t_envi	*cpy;

	cmd = ft_strdup("_");
	if (!cmd)
		return (EXIT_FAILURE);
	value = ft_strdup("/usr/bin/env");
	if (!value)
		return (free(cmd), EXIT_FAILURE);
	cpy = cpy_struct_envi(cmd, value, VALID);
	if (!cpy)
		return (free(cmd), free(value), EXIT_FAILURE);
	add_back_envi(envi, cpy);
	return (EXIT_SUCCESS);
}

//si on a un environnement null, on essaye de retourner la liste envi
//en ajoutant les environnements: PWD, SHLVL et _(underscore)
t_envi	*null_envi(t_envi *envi)
{
	if (pwd_envi(&envi) == EXIT_FAILURE)
		return (NULL);
	if (shlvl_envi(&envi) == EXIT_FAILURE)
		return (free_envi(envi), NULL);
	if (underscore_envi(&envi) == EXIT_FAILURE)
		return (free_envi(envi), NULL);
	return (envi);
}
