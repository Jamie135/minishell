/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:12:21 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/29 17:12:21 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*remove_doll(char *str)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	len;
// 	char	*tmp;

// 	i = 0;
// 	j = 1;
// 	len = ft_strlen((const char *)str);
// 	tmp = malloc(sizeof(char *) * len);
// 	while (j < len)
// 	{
// 		tmp[i] == str[j];
// 		printf("tmp[%li]: %c\n", i, tmp[i]);
// 		i++;
// 		j++;
// 	}
// 	return (tmp);
// }

int	expend_pars_exit(char *str, t_list **join)
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
	ft_bzero(str, ft_strlen(str));
	return (EXIT_SUCCESS);
}

char	*expend_pars_var(t_envi *env, char *str)
{
	char	*new;
	t_list	*join;

	new = NULL;
	join = NULL;
	if (str[0] != '$')
		ft_lstadd_front(&join, ft_lstnew(ft_strdup(str), -1));
	if (str[0] == '$' && is_str_alnum(&str[1]))
	{
		new = add_value_to_ve(&str[1], env);
		if (!new)
			return (NULL);
		return (new);
	}
	str = expend_join(env, &join, str);
	if (expend_pars_exit(str, &join))
		return (NULL);
	new = ft_lstjoin(join);
	return (free_list(join), new);
}

char	*expend_pars_str(t_envi *env, char *str)
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
		tmp = expend_pars_var(env, split[i]);
		if (!tmp)
			return (free_split(split), free_list(join), NULL);
		ft_lstadd_back(&join, ft_lstnew(tmp, -1));
	}
	str = ft_lstjoin(join);
	if (!str)
		return (free_list(join), free_split(split), NULL);
	return (free_list(join), free_split(split), str);
}

void	expend_pars(t_free *free_var, t_envi *env)
{
	int		i;

	i = 0;
	while (env && free_var->split[i])
	{
		// printf("SPLIT: %s ; strchr: %s ; is_dollar: %i\n", \
		// 		free_var->split[i], ft_strchr(free_var->split[i], '$'), \
		// 		is_dollar(free_var->split[i]));
		if (ft_strchr(free_var->split[i], '$') \
			&& !is_dollar(free_var->split[i]))
		{
			free_var->split[i] = expend_pars_str(env, free_var->split[i]);
			// printf("SPLIT[%i]: %s\n", i, free_var->split[i]);
			if (!free_var->split[i])
				return ;
		}
		i++;
	}
}
