/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:55:52 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 16:20:02 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mode_file(int type[2], int mode)
{
	if (mode == INFILE)
	{
		if (type[INFILE] > 0)
			return (1);
	}
	else if (mode == OUTFILE)
	{
		if (type[OUTFILE] > 0)
			return (1);
	}
	return (0);
}

void	valid_next(t_shell *shell, t_list *list, int type[2], int *i)
{
	if (shell->cmd_num == 0)
	{
		shell->infile[0] = mode_file(type, INFILE);
		shell->outfile[0] = mode_file(type, OUTFILE);
	}
	else if (list->type == PIPE || list->next == NULL)
	{
		shell->infile[*i] = mode_file(type, INFILE);
		shell->outfile[*i] = mode_file(type, OUTFILE);
		ft_bzero(type, sizeof(int) * 2);
		(*i)++;
	}
}
