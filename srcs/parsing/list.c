/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:04:22 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 16:20:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*fill(t_free *free_var, t_list *list)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	list->content = free_var->split[0];
	list->unexpended = free_var->unexpended[0];
	list->type = -1;
	while (free_var->split[i])
	{
		tmp = ft_lstnew_2(free_var->split[i], -1,
			free_var->unexpended[i], free_var->quoted[i]);
		if (tmp == NULL)
			return (NULL);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	type(list);
	return (list);
}

t_list	*fill_list(char *str, t_free *free_var)
{
	char	*new;
	t_list	*list;
	char	**tab;

	if (valid_quote(str) == -1)
		return (free_quote(str));
	new = get_string(str);
	if (!new)
		return (free(str), NULL);
	list = NULL;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	tab = split_string(new, ' ');
	if (!tab)
		return (free_fill(tab, list, str));
	if (trim_split(tab, free_var) == -1)
		return (free_list(list), free_split(tab),
			free(str), free(new), NULL);
	list = fill(list, free_var);
	if (!list)
		return (NULL);
	return (free(new), list);
}
