/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:30:42 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 12:55:26 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//update la valeur de exitz
void	get_exit_value(t_shell *shell)
{
	if (shell->mode == 64512)
		shell->mode = 127;
	if (shell->mode == 65280)
		shell->mode = 1;
	else if (shell->mode == 64256)
		shell->mode = 128;
	else if (shell->mode == 5120)
		shell->mode = 127;
	else
	{
		if (shell->mode > 255)
		{
			while (shell->mode > 255)
				shell->mode -= 255;
		}
	}
}

//faire appel aux child proccess dans plusieurs cas differents
int	parent_process(t_shell *shell, t_envi *envi)
{
	int	mode;

	mode = 0;
	if (shell->cmd_num == 0 && shell->redir_num > 0)
		mode = parent_no_cmd(shell);
	if (shell->cmd_num == 1 && shell->redir_num == 0)
		mode = parent_one_cmd(shell);
	else if (shell->cmd_num > 1 && shell->redir_num == 0)
		mode = parent_n_cmd(shell);
	else if (shell->cmd_num == 1 && shell->redir_num > 0)
		mode = parent_one_cmd_redir(shell);
	else if (shell->cmd_num > 1 && shell->redir_num > 0)
		mode = parent_n_cmd_redir(shell);
	if (mode == FAILURE)
	{
		envi = dup_envi(shell->envi);
		if (!envi)
			return (message_free_exit(shell, "execution.c (4)", MALLOC, NULL), \
					EXIT_FAILURE);
		message_free_exit(shell, NULL, errno, NULL);
		return (EXIT_FAILURE);
	}
	heredoc_unlink(shell->list);
	return (EXIT_SUCCESS);
}

//update la variable SHLVL de l'environnement
//convertir la liste t_envi en une liste char **
void	shlvl_var(t_shell *shell)
{
	static int	flag = 0;
	char		*shlvl;
	int			n;

	if (flag == 0)
	{
		shlvl = find_value_envi("SHLVL", shell->envi);
		if (shlvl)
		{
			free_split(shell->environment);
			n = ft_atoi(shlvl);
			n++;
			shlvl = ft_itoa(n);
			if (!shlvl)
				return (malloc_err("execution.c (2)"));
			shell->envi = update_value_envi("SHLVL", shlvl, 0, shell->envi);
			shell->environment = init_env(shell->envi);
			if (shell->environment == ERROR)
				return (malloc_err("execution.c (3)"));
			free(shlvl);
		}
		flag = 1;
	}
}

//execution des commandes
t_envi	*execution(t_list *list, t_envi *env, int *count, int *exit_value)
{
	t_shell	*shell;
	t_envi	*envp;

	if (valid_num_redir(list) == -1 || valid_extra_token(list) == -1 \
		|| valid_after_redir(list) == -1 || valid_pipe(list) == -1)
	{
		*exit_value = 2;
		return (env);
	}
	if (heredoc(list, env, count, exit_value))
		return (free_list(list), env);
	if (expend_list(env, list, *exit_value))
		return (free_list(list), malloc_err("execution.c (1)"), env);
	shell = shell_struct(list, env, count, exit_value);
	if (!shell)
		return (NULL);
	shlvl_var(shell);
	if (parent_process(shell, env))
		return (env);
	envp = dup_envi(shell->envi);
	if (envp == ERROR)
		return (free_shell_1(shell), NULL);
	get_exit_value(shell);
	*exit_value = shell->mode;
	return (free_shell_1(shell), envp);
}
