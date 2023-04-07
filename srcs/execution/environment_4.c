/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:26:22 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/30 21:26:22 by pbureera         ###   ########.fr       */
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

void	print_envi(t_shell *shell, t_envi *envi)
{

}
