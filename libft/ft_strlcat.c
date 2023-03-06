/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:13:30 by pbureera          #+#    #+#             */
/*   Updated: 2022/10/18 23:13:30 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	str;

	i = 0;
	while (*dst && i < size)
	{
		++dst;
		++i;
	}
	str = ft_strlcpy(dst, src, size - i);
	return (str + i);
}
