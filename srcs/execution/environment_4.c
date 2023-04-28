/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:26:22 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 17:16:12 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//update la valeur et type du ve
static int	update_value(t_envi **update, int type, char *value)
{
	if ((*update)->value)
		free((*update)->value);
	(*update)->type = type;
	(*update)->value = ft_strdup(value);
	if (!(*update)->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//chercher le variable environnement dans la struct envi qui match *ve
//update la valeur de *ve dans la liste *envi
t_envi	*update_value_envi(char *ve, char *value, int type, t_envi *envi)
{
	t_envi	*update;
	t_envi	*env;

	if (!envi)
		return (NULL);
	update = NULL;
	env = envi;
	while (envi)
	{
		if (ft_strcmp(envi->ve, ve) == 0)
		{
			update = envi;
			break ;
		}
		envi = envi->next;
	}
	if (update)
	{
		if (update_value(&update, type, value))
			return (NULL);
	}
	return (env);
}

//swap les ve, valeurs et type
void	swap_envi(t_envi *e_1, t_envi *e_2)
{
	char	*ve_tmp;
	char	*value_tmp;
	int		type_tmp;

	ve_tmp = e_1->ve;
	value_tmp = e_1->value;
	type_tmp = e_1->type;
	e_1->ve = e_2->ve;
	e_1->value = e_2->value;
	e_1->type = e_2->type;
	e_2->ve = ve_tmp;
	e_2->value = value_tmp;
	e_2->type = type_tmp;
}

//trier envi
void	sort_envi(t_envi **envi)
{
	int		swap;
	t_envi	*tmp;
	t_envi	*next;

	next = NULL;
	swap = 1;
	if (*envi == NULL)
		return ;
	while (swap)
	{
		swap = 0;
		tmp = *envi;
		while (tmp->next != next)
		{
			if (ft_strcmp(tmp->ve, tmp->next->ve) > 0)
			{
				swap_envi(tmp, tmp->next);
				swap = 1;
			}
			tmp = tmp->next;
		}
		next = tmp;
	}
}

void	print_envi(t_shell *shell, t_envi *envi)
{
	t_envi	*sorted;
	t_envi	*front;

	sorted = dup_envi(envi);
	if (sorted == NULL)
		return ;
	sort_envi(&sorted);
	front = sorted;
	while (sorted)
	{
		if (ft_putstr_fd("declare -x ", STDOUT) == FAILURE || \
			ft_putstr_fd(sorted->ve, STDOUT) == FAILURE)
			return (msgexit(shell, EXPORT_ERR, errno, &exit));
		if (sorted->type == VALID)
		{
			if (ft_putstr_fd("=\"", STDOUT) == FAILURE || \
				ft_putstr_fd(sorted->value, STDOUT) == FAILURE || \
				ft_putstr_fd("\"", STDOUT) == FAILURE)
				return (msgexit(shell, EXPORT_ERR, errno, &exit));
		}
		if (ft_putchar_fd('\n', STDOUT) == FAILURE)
			return (msgexit(shell, EXPORT_ERR, errno, &exit));
		sorted = sorted->next;
	}
	free_envi(front);
}
