/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:44:18 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/23 12:45:28 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_str_alnum_dollars(char *str)
{
	size_t	i;
	size_t	n;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '$' || str[i] == ' ')
			n++;
		i++;
	}
	if (n == len)
		return (1);
	return (0);
}

int	is_inside_closed(char *line)
{
	int		i;
	int		flag;
	char	tmp;

	i = 0;
	flag = -1;
	tmp = 0;
	while (++i < ft_strlen(line) - 1 && line[i] != ' ')
	{
		if ((line[i] == '\'' || line[i] == '\"') && flag == -1)
			flag = 0;
		if ((line[i] == '\'' || line[i] == '\"') && flag == 0)
		{
			tmp = line[i];
			flag = 1;
			i++;
		}
		if (line[i] == tmp && flag == 1)
			flag = 0;
	}
	if (flag)
		return (0);
	return (1);
}

char	*trim_inside(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		flag;

	new_str = malloc(sizeof(char *) * (ft_strlen(str) - 1));
	if (!new_str)
		return (free(str), NULL);
	i = -1;
	j = 0;
	flag = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && flag < 2)
			flag++;
		else
		{
			new_str[j] = str[i];
			j++;
		}
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}
