/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:03:31 by pbureera          #+#    #+#             */
/*   Updated: 2023/06/14 22:03:31 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cpy_var(char *src, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (end - start + 1));
	while (src[start] && i != end - start)
	{
		result[i] = src[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*replace_by_variable(char *src, int start, int end, t_envi *env)
{
	char	*env_line;
	char	*var;

	var = NULL;
	env_line = NULL;
	var = cpy_var(src, start, end);
	env_line = cpy_env_line(var, env);
	return (env_line);
}

int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_end_quote(char *str, char c, int start)
{
	int	n;

	n = 0;
	while (str[start])
	{
		if (str[start] == c)
			n++;
		start++;
	}
	return (n);
}

char	*join_character(char *str, char c)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (str == NULL)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	i++;
	result[i] = '\0';
	free(str);
	return (result);
}
