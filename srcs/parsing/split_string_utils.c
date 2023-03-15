/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:06:30 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/15 20:06:30 by pbureera         ###   ########.fr       */
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

int	increment_word(const char *s, int quote)
{
	size_t	i;

	if (quote == 1)
	{
		i = increment_single_quote(s);
		i--;
		return (i);
	}
	else if (quote == 2)
	{
		i = increment_double_quote(s);
		i--;
		return (i);
	}
}
