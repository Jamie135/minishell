/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:13:13 by pbureera          #+#    #+#             */
/*   Updated: 2022/10/18 23:13:13 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tab;
	size_t	len;

	len = ft_strlen(s);
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s, len + 1);
	return (tab);
}
