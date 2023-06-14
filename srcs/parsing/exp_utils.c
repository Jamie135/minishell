/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:39:56 by pbureera          #+#    #+#             */
/*   Updated: 2023/06/14 22:39:56 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_char(char	*src, int to_remove)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(src) - to_remove + 1));
	while (src[i + to_remove])
	{
		result[i] = src[i + to_remove];
		i++;
	}
	result[i] = '\0';
	free(src);
	return (result);
}

char	*cpy_env_line(char *to_find, t_envi *env)
{
	int		i;
	char	*result;
	t_envi	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(to_find, tmp->ve))
		{
			result = ft_strdup(tmp->value);
			free(to_find);
			return (result);
		}
		tmp = tmp->next;
	}
	free(to_find);
	result = ft_strdup("\0");
	return (result);
}
