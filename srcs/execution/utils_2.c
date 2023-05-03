/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:53:52 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/28 17:37:33 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extra_redir(char *tmp)
{
	if (!ft_strcmp(tmp, "<<"))
	{
		print_token("newline");
		return (-1);
	}
	else if (!ft_strcmp(tmp, ">>"))
	{
		print_token(">");
		return (-1);
	}
	return (0);
}

void	check_arg_behind(t_list *list, size_t *len)
{
	while (list)
	{
		if (list->type == PIPE)
			break ;
		if (list->type == ARG)
			(*len)++;
		list = list->next;
	}
}

int	check_unknown(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -2)
			return (-1);
		i++;
	}
	return (0);
}

int	list_args_2(t_list *list, char **args, size_t *len, size_t *i)
{
	size_t	j;

	j = -1;
	if (*i > 0)
	{
		while (++j < 1 && list->next)
			list = list->next;
	}
	while (list && *i < *len)
	{
		while (list->type != CMD && list->type != ARG)
			list = list->next;
		args[*i] = ft_strdup(list->content);
		if (!args[*i])
			return (free_n_split(args, *i), 0);
		if (list->next)
			list = list->next;
		(*i)++;
	}
	return (1);
}

// while (++j < *i && list->next)
// 	list = list->next;
// printf("args content: %s\n", list->content);

int	is_command(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "echo") \
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset") \
		|| !ft_strcmp(str, "exit") || !ft_strcmp(str, "env") \
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "unset") \
		|| !ft_strcmp(str, "ls") || !ft_strcmp(str, "cat") \
		|| !ft_strcmp(str, "grep") || !ft_strcmp(str, "sleep")
		|| !ft_strcmp(str, "mkdir") || !ft_strcmp(str, "touch")
		|| !ft_strcmp(str, "awk") || !ft_strcmp(str, "wc") \
		|| !ft_strcmp(str, "chmod") || !ft_strcmp(str, "expr")
		|| !ft_strcmp(str, "rm") || !ft_strcmp(str, "./minishell"))
		return (1);
	return (0);
}
