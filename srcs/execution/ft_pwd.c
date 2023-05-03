/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:33:11 by Espéranto         #+#    #+#             */
/*   Updated: 2023/04/28 17:15:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_pwd(t_shell *shell, char *str, int value, void (*f)(int))
{
	if (value < 0)
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
	exit(0);
}

int	ft_pwd(t_shell *shell)
{
	t_envi	*envi;
	char	repertoire_actuel[PATH_MAX];
	char	*tmp;

	envi = shell->envi;
	(void)shell;
	if (!getcwd(repertoire_actuel, sizeof(repertoire_actuel)))
	{
		while (envi)
		{
			if (identique("PWD", (envi->ve)))
				tmp = envi->value;
			envi = envi->next;
		}
		ft_putendl_fd(tmp, STDOUT);
		return (free_pwd(shell, NULL, errno, &exit), EXIT_FAILURE);
	}
	ft_putendl_fd(repertoire_actuel, STDOUT);
	return (EXIT_SUCCESS);
}
