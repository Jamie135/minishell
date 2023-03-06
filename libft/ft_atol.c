/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:28:09 by pbureera          #+#    #+#             */
/*   Updated: 2023/01/19 12:29:22 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*str))
		++str;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign *= -1;
	while (ft_isdigit(*str))
	{
		n = n * 10 + sign * (*str++ - '0');
		if (sign < 0 && n > 0)
			return (LONG_MIN);
		else if (sign > 0 && n < 0)
			return (LONG_MAX);
	}
	return (n);
}
