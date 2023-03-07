/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:52:24 by pbureera          #+#    #+#             */
/*   Updated: 2022/06/13 14:54:40 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	convert;

	i = 0;
	convert = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		convert = (convert * 10) + (str[i] - 48);
		i++;
	}
	return (convert * sign);
}

/*#include <stdio.h>

int main(int argc, char **argv)
{
	int	a;
	int	b;

	a = ft_atoi(argv[1]);
	b = atoi(argv[1]);
	printf("my atoi : %d\nreal atoi : %d\n", a, b);
	return (0);
}*/