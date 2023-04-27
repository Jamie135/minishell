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

//signal_flag va etre utiliser pour gerer les ctrlC/D dans la boucle heredoc 
volatile int	signal_flag = 0;

//handler du signal recu dans heredoc
void	heredoc_handler(int	sig)
{
	if (sig == SIGINT)
	{
		signal_flag = 1;
		write(1, "\n", 1);
		printf("minishell> ");
	}
	else
		return ;
}

//handler du signal recu dans le main
void	minishell_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (signal_flag == 0 || signal_flag == 2)
		{
			signal_flag = 2;
			rl_on_new_line();
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			signal_flag = 0;
	}
	else
		return ;
}

int	parent_child_signal(int pro)
{
	if (pro == MINISHELL)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &minishell_handler);
	}
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
