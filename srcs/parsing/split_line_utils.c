/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:06:30 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 13:10:24 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	increment_single_quote(const char *s)
{
	size_t	i;

	i = 1;
	while (s[i + 1] && s[i] != '\'')
		i++;
	i++;
	return (i);
}

size_t	increment_double_quote(const char *s)
{
	size_t	i;

	i = 1;
	while (s[i + 1] && s[i] != '\"')
		i++;
	i++;
	return (i);
}

int	increment_word(const char *s, bool quote)
{
	size_t	i;

	if (quote == true)
	{
		i = increment_single_quote(s);
		i--;
		return (i);
	}
	else
	{
		i = increment_double_quote(s);
		i--;
		return (i);
	}
}

int	len_split(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}
