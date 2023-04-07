/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:09:34 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 13:43:37 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//retourner la valeur du ve (variable environnement) de envi
char	*find_value_envi(char *name, t_envi *envi)
{
	if (!envi)
		return (NULL);
	while (envi)
	{
		if (ft_strcmp(envi->ve, name) == 0)
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}

//retourner la taille de envi
size_t	len_envi(t_envi *envi)
{
	size_t	len;

	len = 0;
	while (envi)
	{
		if (envi->type == VALID)
			len++;
		envi = envi->next;
	}
	return (len);
}

//joindre ve avec sa valeur
//ex: ve = "USER" et value = "pbureera"
//	  join_envi -> "USER = pbureera"
static int	join_envi(char **env, t_envi *envi, size_t i)
{
	char	*tmp;

	tmp = ft_strjoin(envi->ve, "=");
	if (!tmp)
		return (free_n_split(env, i), EXIT_FAILURE);
	env[i] = ft_strjoin(tmp, envi->value);
	if (!env[i])
		return (free_n_split(env, i), EXIT_FAILURE);
	free_ptr((void **)&tmp);
	return (EXIT_SUCCESS);
}

//convertir une liste t_envi en une liste char ** (envi -> env)
char	**init_env(t_envi *envi)
{
	char	**env;
	size_t	len;
	size_t	i;

	if (!envi)
		return (NULL);
	len = len_envi(envi);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (ERROR);
	i = 0;
	while (i < len)
	{
		if (envi->type == VALID)
		{
			if (join_envi(env, envi, i) == EXIT_FAILURE)
				return (ERROR);
			i++;
		}
		envi = envi->next;
	}
	env[i] = NULL;
	return (env);
}
