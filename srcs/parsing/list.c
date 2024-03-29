/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:04:22 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/04 17:07:11 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_str_dot(char *line)
{
	int	dot;
	int	i;

	dot = 0;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '.'))
	{
		if (line[i] == '.')
			dot++;
		i++;
	}
	if (!dot || line[i])
		return (0);
	else if (dot && !line[i])
		return (dot);
	return (0);
}

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
		tmp = ft_lstnew_2(free_var->split[i], -1, \
							free_var->unexpended[i], free_var->quoted[i]);
		if (tmp == NULL)
			return (NULL);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	type(list);
	return (list);
}

// printf("tmp: %s\n", tmp->content);

// printf("SPLIT[0]: %s\n", list->content);

//creer une liste qui separe la ligne de commande
//ex: echo "hey"'hey' -> [echo][hey][hey]
t_list	*fill_list(char *line, t_free *free_var, t_envi *env, int *exit)
{
	char	*str;
	t_list	*list;
	char	**tab;

	if (valid_quote(line) == -1)
		return (free_quote(line, exit));
	str = get_string(line, env);
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
		return (free_all_trim(list, tab, line, str), NULL);
	list = fill(list, free_var);
	if (!list)
		return (NULL);
	free_var->status = *exit;
	return (free(str), list);
}

// printf("str: %s\n", str);

// if (expend_pars(free_var, env, *exit))
// 	return (free_var_all(free_var), malloc_err("fill_list.c"), NULL);

// int i = 0;
// while (tab[i])
// 	printf("TAB = %s\n", tab[i++]);

// int	i = 0;
// while (free_var->split[i])
// {
// 	printf("SPLIT: %s\n", free_var->split[i]);
// 	i++;
// }

// while (list)
// {
// 	printf("list content: %s ; ", list->content);
// 	printf("type: %i\n", list->type);
// 	list = list->next;
// }

// while (env)
// {
// 	printf("ve: %s\n", env->ve);
// 	printf("value: %s\n", env->value);
// 	env = env->next;
// }
