/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 04:29:20 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 13:39:53 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_spe_var(char *line)
{
	int	i;

	i = 0;
	while (line[i] < (int)ft_strlen(line))
	{
		if (is_special_var(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	dollars_pars(char *line, int *exit)
{
	if (ft_strlen(line) != 2)
	{
		if (find_spe_var(line))
		{
			dollars_message(line, exit);
			return (-1);
		}
		else
			return (-1);
	}
	else
	{
		if (is_special_var(line[1]))
		{
			dollars_message(line, exit);
			return (-1);
		}
		else
			return (-1);
	}
}

void	fill_quote_inc(char *str, char *new, int *i, int j)
{
	new[*i + j] = str[*i];
	(*i)++;
}

void	fill_inc(char *str, char *new, int *i, int j)
{
	new[*i + j] = str[*i];
	(*i)++;
}

//verifier si la syntaxe est correcte (ouverture et fermeture des quotes)
int	valid_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '\'' && i++)
		{
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (syntax_err(line));
		}
		else if (line[i] && line[i] == '\"' && i++)
		{
			while (line[i] && line[i] != '\"')
				i++;
			if (!line[i])
				return (syntax_err(line));
		}
		if (line[i] && (line[i] == ';' || line[i] == 92))
			return (syntax_err(line));
		i++;
	}
	return (0);
}
