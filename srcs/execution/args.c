/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:50:54 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/30 19:50:54 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//retourner la taille de str avant un espace
int	before_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	return (len);
}

//split la commande si on a un espace
int	split_space_cmd(t_list *list, char **args, size_t *i)
{
	if (list->type == CMD && ft_strchr(list->content, ' '))
	{
		args[*i] = ft_substr(list->content, 0, before_space(list->content));
		if (!args[*i])
			return (free_n_split(args, *i), EXIT_FAILURE);
		(*i)++;
		args[*i] = ft_substr(list->content, before_space(list->content) + 1,
				ft_strlen(list->content) - before_space(list->content));
		if (!args[*i])
			return (free_n_split(args, *i), EXIT_FAILURE);
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

//verifier si on a espace dans la commande
int	check_space_cmd(t_list *list)
{
	int	i;

	i = 0;
	while (list && list->type != CMD)
		list = list->next;
	if (list && list->type == CMD)
	{
		while (list->content[i])
		{
			if (list->content[i] == ' ')
				return (1);
			i++;
		}
	}
	return (0);
}

//retourner le nombre d'arguments dans la liste CMD OPT ARG OPT
size_t	len_args(t_list *list)
{
	size_t	len;
	int		space_flag;

	len = 0;
	space_flag = 0;
	if (list == NULL)
		return (len);
	if (is_space_cmd(list))
		space_flag = 1;
	while (list && list->type != CMD)
		list = list->next;
	if (list->type == CMD)
	{
		len++;
		list = list->next;
	}
	while (list && list->type == ARG)
	{
		len++;
		list = list->next;
	}
	return (len + space_flag);
}

//convertir *list en un char ** d'arguments
char	**list_args(t_list *list)
{
	char	**args;
	size_t	len;
	size_t	i;

	if (list == NULL)
		return (NULL);
	len = len_args(list);
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	while (list && list->type != CMD)
		list = list->next;
	i = 0;
	if (split_space_cmd(list, args, &i))
		return (NULL);
	while (list && i < len)
	{
		args[i] = ft_strdup(list->content);
		if (!args[i])
			return (free_n_split(args, i), NULL);
		list = list->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
