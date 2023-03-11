/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:03:03 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/10 21:03:03 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_key(char *env)
{
	int		len;
	char	*key;

	len = 0;
	while (env[len] && && env[len] != '=')
		len++;
	key = ft_substr(env, 0, len);
	if (!key)
		return (NULL);
	return (key);
}

char	*env_value(char *env)
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

t_envi	*cpy_struct_envi(char *key, char *value, int type)
{
	t_envi	*cpy;

	if (!key || !value)
		return (NULL);
	cpy = malloc(sizeof(t_envi));
	if (!cpy)
		return (NULL);
	cpy->key = key;
	cpy->value = value;
	cpy->type = type;
	cpy->next = NULL;
	return (cpy);
}

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

t_envi	init_envi(char **envp)
{
	t_envi	*envi;
	t_envi	*cpy;
	char	*key;
	char	*value;
	int		i;

	if (!envi)
		return (NULL);
	i = 0;
	envi = NULL;
	while (env[i])
	{
		key = env_key(env[i]);
		value = env_value(env[i]);
		if (!key || !value)
			return (free_envi(envi), -1);
		cpy = cpy_struct_envi(key, value, VALID);
		if (!cpy)
			return (free_envi(envi), -1);
		add_back_envi(&envi, cpy);
		i++;
	}
	return (envi);
}
