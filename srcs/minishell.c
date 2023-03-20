/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:10:40 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 16:41:59 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*list;
	t_free	free_var;

	line = NULL;
	list = NULL;
	(void)argc;
	(void)argv;
	run(envp, line, list, &free_var);
	return (0);
}
