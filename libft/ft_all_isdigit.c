/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:13:53 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 17:14:55 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_all_isdigit(char *str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i == len)
		return (1);
	return (0);
}
