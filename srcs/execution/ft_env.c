/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:57:41 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/16 13:57:47 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_envi
{
	char		*ve;
	char		*value;
	struct s_envi	*next;
}	t_envi;

void	ft_env(t_envi *envi)
{
	t_envi	*parcours;

	parcours = envi;
	while (parcours)
	{
		printf("%s=%s\n", parcours->ve, parcours->value);
		parcours = parcours->next;
	}
}
/*
int	main(int ac, char **av, char **env)
{
	t_envi	*envi;

	envi = init_envi(env);
	ft_env(envi);
}
*/
