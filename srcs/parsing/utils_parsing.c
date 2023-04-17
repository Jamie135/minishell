/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 04:29:20 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/18 04:29:20 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_quote_inc(char *str, char *new, int *i, int j)
{
	new[*i + j] = str[*i];
	(*i)++;
}

void	fill_inc(char *str, char *new, int *i, int j)
{
	new[*i + j] = str[*i];
	(*i)++;
}
