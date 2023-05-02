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
int	valid_syntax(char *line, int *exit_value)
{
	int		i;
	char	*tmp;

	i = 0;
	if (space_in_double_quote(line) || space_in_single_quote(line))
	{
		tmp = space_str(line);
		if (tmp)
		{
			ft_putstr_fd(tmp, STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd("command not found", STDERR);
		*exit_value = 127;
		return (-1);
	}
	line = command_in_quoted(line);
	while (line[i])
	{
		if (valid_syntax_2(line, &i) == -1)
			return (syntax_err(line));
		i++;
	}
	return (0);
}
