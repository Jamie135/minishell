/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:11:39 by pbureera          #+#    #+#             */
/*   Updated: 2022/10/18 23:11:39 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*str_dest;
	unsigned char	*str_src;

	str_dest = (unsigned char *)dest;
	str_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		str_dest[i] = str_src[i];
		if (str_dest[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
