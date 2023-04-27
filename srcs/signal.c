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

volatile int	signal_flag = 0;

void	heredoc_handler(int	sig)
{
	if (sig == SIGINT)
	{
		rl_done = 1;
		signal_flag = 1;
		write(1, "\n", 1);
		printf("minishell> ");
	}
	else
		return ;
}

int	parent_heredoc_signal(int pro)
{
	if (pro == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (pro == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (pro == HEREDOC)
	{
		signal(SIGINT, &heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}

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
