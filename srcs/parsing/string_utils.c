/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:36:55 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 16:15:49 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_index(char *str, int index, char c)
{
	int	i;

	i = 0;
	if (c == '\'')
	{
		while (str[++i])
		{
			if (i <= index)
				continue ;
			if (str[i] == '\'')
				return (i);
		}
	}
	else
	{
		while (str[++i])
		{
			if (i <= index)
				continue ;
			if (str[i] == '\"')
				return (i);
		}
	}
	return (i);
}

int	single_quote_index(char *str, char *new, int i, int j)
{
	int	tmp;

	tmp = i;
	while (i <= quote_index(str, tmp, '\''))
	{
		new[i + j] = str[i];
		i++;
	}
	i--;
	return (i);
}

int	double_quote_index(char *str, char *new, int i, int j)
{
	int	tmp;

	tmp = i;
	while (i <= quote_index(str, tmp, '\"'))
	{
		new[i + j] = str[i];
		i++;
	}
	i--;
	return (i);
}

int	new_string_single(char *new, char *str, char c)
{
	if (c == '>')
	{
		new[0] = ' ';
		new[1] = str[0];
		new[2] = ' ';
	}
	if (c == '<')
	{
		new[0] = ' ';
		new[1] = str[0];
		new[2] = ' ';
	}
	return (1);
}

int	new_string_double(char *new, char *str, char c)
{
	if (c == '>')
	{
		new[0] = ' ';
		new[1] = str[0];
		new[2] = '>';
		new[3] = ' ';
	}
	else
	{
		new[0] = ' ';
		new[1] = str[0];
		new[2] = '<';
		new[3] = ' ';
	}
	return (2);
}
