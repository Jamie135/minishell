/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:35:21 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 15:24:00 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifier si les quotes ouverts sont fermes
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

int	is_unexpended(char *str)
{
	int	i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
			{
				if (str[i] == '\"')
					break;
				if (str[i] == '$')
					return (1);
			}
			if (!str[i])
				return (0);
		}
	}
	return (0);
}

int	is_quoted(char *str)
{
	int	i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[++i] && str[i] != '\'')
				i++;
			if (str[i])
				return (1);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[++i] && str[i] != '\"')
				i++;
			if (str[i])
				return (1);
		}
	}
	return (0);
}
