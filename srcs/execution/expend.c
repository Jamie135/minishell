/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:48:23 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/02 16:13:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//meme principe que expend_str pour une liste
int	expend_list(t_envi *envi, t_list *list, int exit_value)
{
	t_list	*lst;

	lst = NULL;
	while (envi && list)
	{
		if (ft_strchr(list->content, '$') && list->unexpended == false \
			&& !is_dollar(list->content))
		{
			list->content = expend_str(envi, list->content, exit_value);
			if (!list->content)
				return (EXIT_FAILURE);
		}
		lst = list;
		list = list->next;
	}
	return (EXIT_SUCCESS);
}

// if (!ft_strcmp(list->content, ""))
// 				free_one_list(&list, lst);

//expend pour les variables speciales
//ex: $1, $$, ...
int	expend_exit(char *str, t_list **join, int exit_value)
{
	char	*to_join;

	to_join = NULL;
	if (!ft_strcmp("$", str))
	{
		to_join = ft_strdup("$");
		if (!to_join)
			return (EXIT_FAILURE);
		ft_lstadd_front(join, ft_lstnew(to_join, -1));
	}
	else if (!ft_strcmp("$?", str))
	{
		to_join = ft_itoa(exit_value);
		if (!to_join)
			return (EXIT_FAILURE);
		ft_lstadd_front(join, ft_lstnew(to_join, -1));
	}
	ft_bzero(str, ft_strlen(str));
	return (EXIT_SUCCESS);
}

//joindre la variable expended str a la liste **join
//puis retourner la variable 
//ex:	on a e$A avec $A = cho
//		expend_join va joindre e avec $A
//		on obtient ainsi e$A = echo
char	*expend_join(t_envi *envi, t_list **join, char *str)
{
	size_t	i;
	size_t	len;
	char	*to_join;

	i = 0;
	len = ft_strlen(str);
	while (str[0] == '$' && !is_str_alnum(&str[1]) && len--)
	{
		if (len == 1 && is_special_var(str[1]))
			break ;
		to_join = ft_strdup(&str[len]);
		if (!to_join)
			return (NULL);
		str[len] = '\0';
		ft_lstadd_front(join, ft_lstnew(to_join, -1));
		i++;
	}
	if (!is_special_var(str[1]))
	{
		to_join = give_value(&str[1], envi);
		if (!to_join)
			return (NULL);
		ft_lstadd_front(join, ft_lstnew(to_join, -1));
	}
	return (str);
}

//trouver la variable expended pour join avec expend_join
char	*expend_var(t_envi *envi, char *str, int exit_value)
{
	char	*new;
	t_list	*join;

	new = NULL;
	join = NULL;
	if (str[0] != '$')
		ft_lstadd_front(&join, ft_lstnew(ft_strdup(str), -1));
	if (str[0] == '$' && is_str_alnum(&str[1]))
	{
		new = add_value_to_ve(&str[1], envi);
		if (!new)
			return (NULL);
		return (new);
	}
	str = expend_join(envi, &join, str);
	if (expend_exit(str, &join, exit_value))
		return (NULL);
	new = ft_lstjoin(join);
	return (free_list(join), new);
}

//gestion des expended variables
//ex : $A = "cho" -> e$A = echo
char	*expend_str(t_envi *envi, char *str, int exit_value)
{
	t_list	*join;
	char	*tmp;
	char	**split;
	int		i;

	join = NULL;
	tmp = add_space_to_dollars(str);
	if (!tmp)
		return (NULL);
	split = ft_split(tmp, -1);
	if (!split)
		return (NULL);
	free_ptr((void **)&tmp);
	i = -1;
	while (split[++i])
	{
		tmp = expend_var(envi, split[i], exit_value);
		if (!tmp)
			return (free_split(split), free_list(join), NULL);
		ft_lstadd_back(&join, ft_lstnew(tmp, -1));
	}
	str = ft_lstjoin(join);
	if (!str)
		return (free_list(join), free_split(split), NULL);
	return (free_list(join), free_split(split), str);
}
