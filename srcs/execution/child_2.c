/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:40:11 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/11 20:40:11 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_pipe_in_out(t_shell *shell)
{
	
}

void	child_n_cmd_redir(t_shell *shell)
{
	const int	id = shell->cid;

	if (shell->infile[id] && shell->outfile[id])
		
}
