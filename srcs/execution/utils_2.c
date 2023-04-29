/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:53:52 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 17:37:33 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	list_args_2(t_list *list, char **args, size_t *len, size_t *i)
{
	size_t	j;

	j = -1;
	if (*i > 0)
	{
		while (++j < 1 && list->next)
			list = list->next;
	}
	while (list && *i < *len)
	{
		args[*i] = ft_strdup(list->content);
		if (!args[*i])
			return (free_n_split(args, *i), 0);
		if (list->next)
			list = list->next;
		(*i)++;
	}
	return (1);
}

// while (++j < *i && list->next)
// 	list = list->next;
// printf("args content: %s\n", list->content);
