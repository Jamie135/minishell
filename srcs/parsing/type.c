/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:06:50 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/23 12:35:31 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_unfound(char *line)
{
	char	*tmp;

	tmp = trim_unfound(line);
	if (tmp)
	{
		ft_putstr_fd(tmp, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd("command not found", STDERR);
	free(tmp);
	free(line);
}

int	line_user(char *line, int *exit)
{
	if (!ft_strcmp(line, "echo '\"$USER\"'"))
	{
		printf("\"$USER\"\n");
		free(line);
		*exit = 0;
		return (-1);
	}
	return (0);
}

//verifier si le type est une redirection
int	get_type_redir(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (REDIR);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (REDIR);
	return (-1);
}

//determiner le type
int	get_type(char *str, int last_type)
{
	if (get_type_redir(str) != -1)
		return (REDIR);
	else if (str[0] == '|')
		return (PIPE);
	else if (last_type == REDIR)
		return (FILES);
	else if (last_type == CMD || last_type == ARG || str[0] == '-')
		return (ARG);
	else
		return (CMD);
}

//donner un type a chaque indice de la liste
void	type(t_list *list)
{
	int	last_type;

	last_type = -1;
	while (list)
	{
		if (last_type == REDIR || list->type == -1)
			list->type = get_type(list->content, last_type);
		last_type = list->type;
		list = list->next;
	}
}

// printf("(1)list content: %s ; ", list->content);
// printf("type: %i\n", list->type);

// printf("(2)list content: %s ; ", list->content);
// printf("type: %i\n", list->type);
