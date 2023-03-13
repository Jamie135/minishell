/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:03:03 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/13 13:39:40 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_cmd(char *env)
{
	int		len;
	char	*cmd;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	cmd = ft_substr(env, 0, len);
	if (!cmd)
		return (NULL);
	return (cmd);
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

t_envi	*cpy_struct_envi(char *cmd, char *value, int type)
{
	t_envi	*cpy;

	if (!cmd || !value)
		return (NULL);
	cpy = malloc(sizeof(t_envi));
	if (!cpy)
		return (NULL);
	cpy->cmd = cmd;
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

t_envi	*init_envi(char **envp)
{
	t_envi	*envi;
	t_envi	*cpy;
	char	*cmd;
	char	*value;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	envi = NULL;
	while (envp[i])
	{
		cmd = env_cmd(envp[i]);
		value = env_value(envp[i]);
		if (!cmd || !value)
			return (free_envi(envi), -1);
		cpy = cpy_struct_envi(cmd, value, VALID);
		if (!cpy)
			return (free_envi(envi), -1);
		add_back_envi(&envi, cpy);
		i++;
	}
	return (envi);
}
