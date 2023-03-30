/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:51:54 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/30 23:51:54 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_no_cmd(t_shell *shell)
{
	const int	id = shell->cid;
	int			infile;
	int			outfile;

	infile = -1;
	outfile = -1;
	infile = open_infile(shell, shell->redir[id]);
	close_fd(&infile);
	outfile = open_outfile(shell, shell->redir[id]);
	close_fd(&outfile);
	free_shell_1(shell);
	exit(EXIT_SUCCESS);
}
