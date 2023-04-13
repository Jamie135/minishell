/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:03:03 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/13 15:52:33 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//retourner la variable d'environnement de envp[i]
char	*variable_env(char *env)
{
	int		len;
	char	*ve;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	ve = ft_substr(env, 0, len);
	if (!ve)
		return (NULL);
	return (ve);
}

//retourner la valeur de la variable d'environnement de envp[i]
char	*value_env(char *env)
{
	int		len;
	char	*value;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	value = ft_substr(env, len + 1, ft_strlen(env) - len);
	if (!value)
		return (NULL);
	return (value);
}

//attribuer les valeurs de ve, value et type au struct cpy
t_envi	*cpy_struct_envi(char *ve, char *value, int type)
{
	t_envi	*cpy;

	if (!ve || !value)
		return (NULL);
	cpy = malloc(sizeof(t_envi));
	if (!cpy)
		return (NULL);
	cpy->ve = ve;
	cpy->value = value;
	cpy->type = type;
	cpy->next = NULL;
	return (cpy);
}

//ajouter la struct cpy a la fin de la liste envi
void	add_back_envi(t_envi **envi, t_envi *cpy)
{
	t_envi	*back;

	if (!envi || !cpy)
		return ;
	if (!*envi)
	{
		*envi = cpy;
		return ;
	}
	back = get_last_envi(*envi);
	back->next = cpy;
}

//creer une "copie" de l'environnement sous forme d'une liste de struct envi
t_envi	*init_envi(char **envp)
{
	t_envi	*envi;
	t_envi	*cpy;
	char	*ve;
	char	*value;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	envi = NULL;
	while (envp[i])
	{
		ve = variable_env(envp[i]);
		value = value_env(envp[i]);
		if (!ve || !value)
			return (free_envi(envi), ERROR);
		cpy = cpy_struct_envi(ve, value, VALID);
		if (!cpy)
			return (free_envi(envi), ERROR);
		add_back_envi(&envi, cpy);
		i++;
	}
	return (envi);
}
