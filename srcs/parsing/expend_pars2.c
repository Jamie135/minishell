/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_pars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:09:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/06/14 22:09:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_env(char *str, t_expand *exp, int j, t_envi *env)
{
	char    *to_join;
    char    *tmp;

    to_join = NULL;
    to_join = replace_by_variable(str, j, exp->i, env);
    tmp = exp->result;
    exp->result = ft_strjoin(exp->result, to_join);
    free(tmp);
    free(to_join);
}

void	expand_found_dollar(t_expand *exp, char *str, t_envi *env)
{
	int		j;
	char	*tmp;

	j = 0;
	exp->i++;
	if (str[exp->i] == '?')
	{
		tmp = exp->result;
		exp->result = ft_strjoin(exp->result, "$?");
		exp->i++;
		free(tmp);
	}
	else
	{
		j = exp->i;
		while (str[exp->i] && !ft_isset(str[exp->i], " /.$!:,'\"+-%%"))
			exp->i++;
		expand_env(str, exp, j, env);
	}
}

void	expand_found_quote(t_expand *exp, char *str)
{
	char	c;
	char	*tmp;

	c = str[exp->i];
	tmp = exp->result;
	if (find_end_quote(str, c, exp->i) == 2)
	{
		exp->result = join_character(exp->result, str[exp->i]);
		exp->i++;
		while (str[exp->i] != c)
		{
			exp->result = join_character(exp->result, str[exp->i]);
			exp->i++;
		}
	}
	else
	{
		exp->result = join_character(exp->result, str[exp->i]);
		exp->i++;
	}
}

void	expand_base(t_expand *exp, char *str, t_envi *env)
{
	char	*tmp;

	if (str[exp->i] == '\'' || str[exp->i] == '"')
		expand_found_quote(exp, str);
	else if (str[exp->i] == '$' && str[exp->i + 1])
		expand_found_dollar(exp, str, env);
	else
	{
		tmp = 
		exp->result = join_character(exp->result, str[exp->i]);
		exp->i++;
	}
}

// printf("res1: %s\n", exp->result);
// printf("res2: %s\n", exp->result);

char	*expand(char *str, t_envi *env)
{
	t_expand	*exp;
	char		*result;

	exp = malloc(sizeof(t_expand));
	exp->i = 0;
	exp->result = malloc(sizeof(char));
	exp->result[0] = '\0';
	while (str[exp->i])
		expand_base(exp, str, env);
	free(str);
	result = ft_strdup(exp->result);
	free(exp->result);
	free(exp);
	return (result);
}
