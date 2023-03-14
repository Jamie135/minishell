/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:04:22 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 17:27:03 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*fill_list(char *str, t_free *to_free)
{
	t_list	*list;
	char	**dup;
	char	*new;

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
	dup = split_parsing(new, ' ');
}
