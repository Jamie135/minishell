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

//recopier les valeurs de la struct t_free a la struct t_list
t_list	*fill(t_list *list, t_free *free_var)
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

//creer une liste qui separe la ligne de commande
//ex: echo "hey"'hey' -> [echo][hey][hey]
t_list	*fill_list(char *line, t_free *free_var)
{
	char	*str;
	t_list	*list;
	char	**tab;

	if (valid_quote(line) == -1)
		return (free_quote(line));
	str = get_string(line);
	if (!str)
		return (free(line), NULL);
	list = NULL;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	tab = split_line(str, ' ');
	if (!tab)
		return (free_fill(tab, list, line));
	if (trim_split(tab, free_var) == -1)
		return (free_list(list), free_split(tab),
			free(line), free(str), NULL);
	list = fill(list, free_var);
	if (!list)
		return (NULL);
	return (free(str), list);
}
