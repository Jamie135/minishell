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

int	ft_env(t_shell *shell)
{
	size_t		i;
	const int	cid = shell->cid;

	if (!shell->environment)
		return (EXIT_SUCCESS);
	i = 0;
	while (shell->environment[i])
	{
		printf("%s\n", shell->environment[i]);
		i++;
	}
	return (SUCCESS);
}
