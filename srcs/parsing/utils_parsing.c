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
	while (i < (int)ft_strlen(line))
	{
		if (dollar_special_var(line[i]))
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
		if (dollar_special_var(line[1]))
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
int	valid_syntax(char *line, int *exit_value)
{
	int		i;

	i = 0;
	if (space_in_double_quote(line) || space_in_single_quote(line))
	{
		spacecmd_not_found(line, exit_value);
		return (-1);
	}
	if (only_quotes(line, exit_value))
		return (-1);
	return (0);
}

// while (line[i])
// {
// 	if (valid_syntax_2(line, &i) == -1)
//		return (syntax_err(line));
// 	i++;
// }
