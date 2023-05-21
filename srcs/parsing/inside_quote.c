/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:44:18 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/21 18:44:18 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_inside_closed(char *line)
{
	int		i;
	int		flag;
	char	tmp;

	i = -1;
	flag = -1;
	tmp = 0;
	while (line[++i])
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

char	*trim_inside(char *line)
{
	char	*new;
	int		i;
	int		j;
	char	tmp;

	new = malloc(sizeof(char *) * (ft_strlen(line) - 1));
	if (!new)
		return (line);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i++;
		else
		{
			new[j] = line[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}
