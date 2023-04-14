/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:57:15 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/11 23:57:15 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


// SIG_IGN dit d'ignorer le signal ctrl+
void	sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrlc);
}
