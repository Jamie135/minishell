/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:59:52 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 15:07:07 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_split_index(char **split, int index, int message)
{
	int	i;

	i = 0;
	if (message = 1)
		ft_putendl_fd("syntax error", 2);
	while (i < index)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}
