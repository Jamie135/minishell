/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:32:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 16:50:26 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_pipe(char *str)
{
	int	len;
	int	i;
	
	if (str && str[0])
		len = ft_strlen(str);
	else
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			len += 2;
			while (str[i] == '|')
				i++;
		}
		else
			i++;
	}
	return (len + i);
}

void	complete_string(char *new, int *i, int *j, char *str)
{
	new[*i + *j] = str[*i];
	(*j)++;
	new[*i + *j] = ' ';
	(*i)++;
	while (str[*i] && str[*i] == '|')
	{
		new[*i + *j] = str[*i];
		(*i)++;
	}
	new[*i + *j] = ' ';
	(*j)++;
	new[*i + *j] = str[*i];
}

char	*split_pipe(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (len_pipe(str) + 2));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	while (str[++i])
	{
		if (str[i] == '\'')
			i = single_quote_index(str, new, i, j) + 1;
		else if (str[i] == '\"')
			i = double_quote_index(str, new, i, j) + 1;
		else if (str[i] != ' ' && str[i + 1] && str[i + 1] == '|')
			complete_string(new, &i, &j, str);
		else
			new[i + j] = str[i];
	}
	new[i + j] = '\0';
	return (free(str), new);
}
