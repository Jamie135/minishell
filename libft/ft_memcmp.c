/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:11:54 by pbureera          #+#    #+#             */
/*   Updated: 2022/10/18 23:11:54 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str_s1;
	unsigned char	*str_s2;

	i = 0;
	str_s1 = (unsigned char *)s1;
	str_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str_s1[i] == str_s2[i] && i < n - 1)
	{
		i++;
	}
	return (str_s1[i] - str_s2[i]);
}
