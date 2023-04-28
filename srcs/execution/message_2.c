/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:31:58 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 13:39:15 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dollars_message(char *line, int *exit)
{
	ft_putstr_fd(line, STDOUT);
	ft_putchar_fd(':', STDOUT);
	ft_putendl_fd(" command not found", STDOUT);
	*exit = 127;
}

static void	message_exit(char **args, const int n)
{
	if (n == 1)
		return ;
	else if (n >= 2 && ft_all_isdigit(args[1]))
	{
		ft_putstr_fd("exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else
		ft_putendl_fd("exit\nexit: too many arguments", STDERR);
}

static void	message(char *str, int value, char **args)
{
	const int	n = len_array(args);

	if (value == MALLOC)
		malloc_err(str);
	else if (value == SYNTAX)
		ft_putendl_fd("syntaxe error", STDERR);
	else if (value == PATH)
		ft_putendl_fd("PATH not set", STDERR);
	else if (value == COMMAND)
	{
		if (str)
		{
			ft_putstr_fd(str, STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd("command not found", STDERR);
	}
	else if (value == EXIT)
		message_exit(args, n);
}

void	message_free_exit(t_shell *shell, char *str, int value, void (*f)(int))
{
	if (value > 0 && str)
		perror(str);
	else if (value > 0)
		ft_putendl_fd(strerror(errno), STDERR);
	else if (value < 0)
		message(str, value, shell->args[shell->cid]);
	if (!f && shell)
		free_shell_1(shell);
	if (f)
	{
		if (shell)
		{
			if (shell->pipes)
				close_pipes(shell->pipes, (shell->cmd_num - 1));
			free_shell_1(shell);
		}
		f(value);
	}
}

//message d'erreur pour les builtins
void	message_builtins(char *cmd, char *arg, char *str)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (arg && ft_strcmp(cmd, "cd") == 0)
	{
		ft_putstr_fd(arg, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	else if (arg && ft_strcmp(cmd, "export") == 0)
	{
		ft_putchar_fd('`', STDERR);
		ft_putstr_fd(arg, STDERR);
		ft_putstr_fd("': ", STDERR);
	}
	if (str)
		ft_putendl_fd(str, STDERR);
}
