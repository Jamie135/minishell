/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:46:54 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 14:37:18 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pid_return(int mode)
{
	if (mode == 130)
		ft_putchar_fd('\n', STDERR);
	else if (mode == 131)
		ft_putendl_fd("Quit (core dumped)", STDERR);
	else
		return ;
}

//retourner le len de **args 
int	len_array(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

//verifier si str est composer uniquement de caractere alphanumerique
int	is_str_alnum(char *str)
{
	size_t	i;
	size_t	n;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			n++;
		i++;
	}
	if (n == len)
		return (1);
	return (0);
}

static void	exit_alphabet(t_list *list, t_envi *env)
{
	const int	num_cmd = num_command(list);
	
	if (ft_strcmp("exit", list->content) == 0)
	{
		if (list->next && list->next->content)
		{
			if (ft_all_isdigit(list->next->content) && num_cmd == 1)
			{
				ft_putendl_fd("exit", STDERR);
				ft_putstr_fd("exit: ", STDERR);
				ft_putstr_fd(list->next->content, STDERR);
				ft_putendl_fd(": numeric argument required", STDERR);
				if (env)
					ft_free_envi(env);
				ft_free_lst(list);
				exit(2);
			}
		}
	}
}

void	do_exit(t_list *list, t_envi *env, char *line, t_free *free_var)
{
	const size_t	size = ft_lstsize(list);
	int				exit_value;

	exit_value = 0;
	free(free_var->unexpended);
	free(free_var->split);
	free(free_var->quoted);
	free(line);
	exit_alphabet(list, env);
	if (ft_strcmp(list->content, "exit") == 0 && size <= 2)
	{
		if (list->next && list->next->content)
			exit_value = ft_atoi(list->next->content);
		ft_putendl_fd("exit", STDERR);
		if (env)
			free_envi(env);
		free_list(list);
		while (exit_value > 255)
			exit_value -= 256;
		exit(exit_value);
	}
}
