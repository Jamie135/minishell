/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:33:11 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/16 11:33:19 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	repertoire_actuel[PATH_MAX];

	(void)shell;
	if (!getcwd(repertoire_actuel, sizeof(repertoire_actuel)))
		return (message_free_exit(shell, NULL, errno, &exit), EXIT_FAILURE);
	ft_putendl_fd(repertoire_actuel, STDOUT);
	return (EXIT_SUCCESS);
}
