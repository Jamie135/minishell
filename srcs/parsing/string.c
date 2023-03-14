/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:13:37 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 15:29:05 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_len(char *str)
{
	int	size;
	int	i;

	i = -1;
	size = (int)ft_strlen(str);
	while (str[++i])
	{
		if (i > 0 && str[i] == '>' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '>'))
		{
			if (str[i + 1] == '>')
				i += 1;
			size += 3;
		}
		else if (i > 0 && str[i] == '<' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '<'))
		{
			if (str[i + 1] == '<')
				i += 1;
			size += 3;
		}
	}
	return (size + i);
}

char	*new_string(char *str)
{
	int			i;
	int			j;
	char		*new;
	const int	size = ft_strlen(str);

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), (new_len(str) + 2));
	if (!new)
		return (NULL);
	while (i <= size)
	{
		if (str[i] == '\'')
			i = 
	}
	
}