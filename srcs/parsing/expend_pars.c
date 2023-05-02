/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:12:21 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/30 11:58:00 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	expend_pars_exit(char *str, t_list **join)
// {
// 	char	*to_join;

// 	to_join = NULL;
// 	if (!ft_strcmp("$", str))
// 	{
// 		to_join = ft_strdup("$");
// 		if (!to_join)
// 			return (EXIT_FAILURE);
// 		ft_lstadd_front(join, ft_lstnew(to_join, -1));
// 	}
// 	ft_bzero(str, ft_strlen(str));
// 	return (EXIT_SUCCESS);
// }

// char	*expend_pars_var(t_envi *env, char *str)
// {
// 	char	*new;
// 	t_list	*join;

// 	new = NULL;
// 	join = NULL;
// 	if (str[0] != '$')
// 		ft_lstadd_front(&join, ft_lstnew(ft_strdup(str), -1));
// 	if (str[0] == '$' && is_str_alnum(&str[1]))
// 	{
// 		new = add_value_to_ve(&str[1], env);
// 		if (!new)
// 			return (NULL);
// 		return (new);
// 	}
// 	str = expend_join(env, &join, str);
// 	if (expend_pars_exit(str, &join))
// 		return (NULL);
// 	new = ft_lstjoin(join);
// 	return (free_list(join), new);
// }

// char	*expend_pars_str(t_envi *env, char *str)
// {
// 	t_list	*join;
// 	char	*tmp;
// 	char	**split;
// 	int		i;

// 	join = NULL;
// 	tmp = add_space_to_dollars(str);
// 	if (!tmp)
// 		return (NULL);
// 	split = ft_split(tmp, -1);
// 	if (!split)
// 		return (NULL);
// 	free_ptr((void **)&tmp);
// 	i = -1;
// 	while (split[++i])
// 	{
// 		tmp = expend_pars_var(env, split[i]);
// 		if (!tmp)
// 			return (free_split(split), free_list(join), NULL);
// 		ft_lstadd_back(&join, ft_lstnew(tmp, -1));
// 	}
// 	str = ft_lstjoin(join);
// 	if (!str)
// 		return (free_list(join), free_split(split), NULL);
// 	return (free_list(join), free_split(split), str);
// }

int	len_space_str(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\"')
	{
		j = i;
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] != '\"')
			return (0);
	}
	else if (line[i] == '\'')
	{
		j = i;
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] != '\'')
			return (0);
	}
	return (i - j);
}

char	*space_str(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = len_space_str(str);
	tmp = malloc(sizeof(char *) * (len + 1));
	if (!tmp)
		return (NULL);
	while (++i < len)
		tmp[i] = ' ';
	tmp[i] = '\0';
	return (tmp);
}

int	expend_pars(t_free *free_var, t_envi *env, int exit_value)
{
	int		i;

	i = 0;
	while (env && free_var->split[i])
	{
		if (ft_strchr(free_var->split[i], '$') \
			&& !is_dollar(free_var->split[i]))
		{
			free_var->split[i] = expend_str(env, free_var->split[i], \
											exit_value);
			if (!free_var->split[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// printf("SPLIT: %s ; strchr: %s ; is_dollar: %i\n",
// 		free_var->split[i], ft_strchr(free_var->split[i], '$'),
// 		is_dollar(free_var->split[i]));

// printf("SPLIT[%i]: %s\n", i, free_var->split[i]);
