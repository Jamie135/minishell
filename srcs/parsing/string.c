/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:13:37 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 16:52:33 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_string(char *str)
{
	int	size;
	int	i;

	i = -1;
	size = (int)ft_strlen(str);
	while (str[++i])
	{
		if (i > 0 && str[i] == '>' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '>'))
		{
			if (str[i + 1] == '>')
				i += 1;
			size += 3;
		}
		else if (i > 0 && str[i] == '<' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '<'))
		{
			if (str[i + 1] == '<')
				i += 1;
			size += 3;
		}
	}
	return (size + i);
}

static void	string_1(int *i, int *j, char *str, char *new)
{
	if (str[*i + 1] && str[*i + 1] == '>')
		*i += new_string_double(&new[*i + *j], &str[*i], '>');
	else
		*i += new_string_single(&new[*i + *j], &str[*i], '>');
	*j += 2;
	if (str[*i] && str[*i] != '>')
		new[*i + *j] = str[*i];
}

static void	string_2(int *i, int *j, char *str, char *new)
{
	if (str[*i + 1] && str[*i + 1] == '<')
		*i += new_string_double(&new[*i + *j], &str[*i], '<');
	else
		*i += new_string_single(&new[*i + *j], &str[*i], '<');
	*j += 2;
	if (str[*i] && str[*i] != '<')
		new[*i + *j] = str[*i];
}

char	*final_string(char *new)
{
	new = split_pipe(new);
	if (!new)
		return (NULL);
	else
		return (new);	
}

char	*get_string(char *str)
{
	int			i;
	int			j;
	char		*new;
	const int	size = ft_strlen(str);

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), (len_string(str) + 2));
	if (!new)
		return (NULL);
	while (i <= size)
	{
		if (str[i] == '\'')
			i = single_quote_index(str, new, i, j) + 1;
		else if (str[i] == '\"')
			i = double_quote_index(str, new, i, j) + 1;
		else if (str[i] && str[i] == '>')
			string_1(&i, &j, str, new);
		else if (str[i] && str[i] == '<')
			string_2(&i, &j, str, new);
		else
			new[i + j] = str[i];
			i++;
	}
	return (final_string(new));
}
