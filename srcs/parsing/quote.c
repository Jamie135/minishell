/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:54:21 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 17:15:33 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_single(char *str, int *single_quote, int *double_quote, int *i)
{
	if (*single_quote == 1)
		*single_quote = 0;
	else
		*single_quote = 1;
	while (str[*i] && str[*i] != '\'')
	{
		if (str[*i] == '\"')
		{
			if (*double_quote == 1)
				*double_quote = 0;
			else
				*double_quote = 1;
		}
		(*i)++;
	}
	if (!str[*i] && (*single_quote == 1 || *single_quote == 1))
		return (-1);
	else
	{
		if (*single_quote == 0)
			*single_quote = 1;
		else
			*single_quote = 0;
	}
	return (0);
}

int	valid_double(char *str, int *single_quote, int *double_quote, int *i)
{
	if (*double_quote == 0)
				*double_quote = 1;
	else
		*double_quote = 0;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '\'')
		{
			if (*single_quote == 1)
				*double_quote = 0;
			else
				*single_quote = 1;
		}
		(*i)++;
	}
	if (!str[*i] && (*single_quote == 1 || *single_quote == 1))
		return (-1);
	else
	{
		if (*single_quote == 0)
			*single_quote = 1;
		else
			*single_quote = 0;
	}
	return (0);
}

int	valid_open(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (-1);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (-1);
		}
	}
	return (0);
}

int	valid_quote(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			if (valid_single(str, &single_quote, &double_quote, &i) == -1)
				return (-1);
		if (str[i] == '\"')
			if (valid_double(str, &single_quote, &double_quote, &i) == -1)
				return (-1);		
	}
	if (valid_open(str) == -1)
		return (-1);
	return (0);
}
