/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:32:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/04 17:11:42 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dots_not_found(char *line, int *exit_value)
{
	if (is_str_dot(line) == 1)
	{
		ft_putstr_fd(".", STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd("command not found", STDERR);
		free(line);
		*exit_value = 127;
		return (-1);
	}
	else if (is_str_dot(line) == 2)
	{
		ft_putstr_fd("..", STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd("command not found", STDERR);
		free(line);
		*exit_value = 127;
		return (-1);
	}
	return (0);
}

int	len_unfound(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] != '\'' && line[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

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
			i = single_quote_index(str, new, i, j);
		if (str[i] == '\"')
			i = double_quote_index(str, new, i, j);
		else if (str[i] != ' ' && str[i + 1] && str[i + 1] == '|')
			complete_string(new, &i, &j, str);
		else
			new[i + j] = str[i];
	}
	new[i + j] = '\0';
	return (free(str), new);
}
