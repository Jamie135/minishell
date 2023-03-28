/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:04:23 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 00:04:23 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_one_envi(t_envi *envi)
{
	free_ptr((void **)&envi->ve);
	free_ptr((void **)&envi->value);
	free_ptr((void **)&envi);
}
