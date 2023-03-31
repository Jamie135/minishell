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

#include <limits.h>
#include <unistd.h>
#include <stdio.h>

void	ft_pwd(void)
{
	char	repertoire_actuel[PATH_MAX];

	if (getcwd(repertoire_actuel, sizeof(repertoire_actuel)))
		printf("%s\n", repertoire_actuel);
}

int	main(void)
{
	ft_pwd();
}
