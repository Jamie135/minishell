/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 04:59:38 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/18 04:59:38 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_quote(char *str)
{
	int	len;
	int	i;

	i = -1;
	len = (int)ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[i] && str[i] == '\'')
				i++;
			len += 2;
		}
		if (str[i] == '\"')
		{
			while (str[i] && str[i] == '\"')
				i++;
			len += 2;
		}
		if (!str[i])
			return (len + i);
	}
	return (len + i);
}

void	fill_quote_single_space(char *str, char *new, int *i, int *j)
{
	*i = single_quote_index(str, new, *i, *j) + 1;
	if (str[*i] && str[*i] != ' ')
	{
		new[*i + *j] = -2;
		(*j)++;
	}
	new[*i + *j] = ' ';
	(*j)++;
}

void	fill_quote_double_space(char *str, char *new, int *i, int *j)
{
	*i = double_quote_index(str, new, *i, *j) + 1;
	if (str[*i] && str[*i] != ' ')
	{
		new[*i + *j] = -2;
		(*j)++;
	}
	new[*i + *j] = ' ';
	(*j)++;
}

char	*string_quote(char *str)
{
	char		*new;
	int			i;
	int			j;
	const int	size = ft_strlen(str);

	j = 0;
	i = 0;
	new = ft_calloc(sizeof(char), (len_quote(str) + 2));
	if (!new)
		return (NULL);
	while (i <= size)
	{
		if (str[i] == '$' && str[i + 1]
			&& (str[i + 1] == '\'' || str[i + 1] == '\"') && i++)
				j--;
		if (str[i] == '\'')
			fill_quote_single_space(str, new, &i, &j);
		else if (str[i] == '\"')
			fill_quote_double_space(str, new, &i, &j);
		else
			fill_quote_inc(str, new, &i, j);
	}
	free(str);
	return (new);
}
