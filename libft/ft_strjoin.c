/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:13:21 by pbureera          #+#    #+#             */
/*   Updated: 2022/10/18 23:13:21 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	tab = malloc(sizeof(char) * (len + 1));
	if (tab == 0)
		return (NULL);
	ft_strlcpy(tab, s1, len + 1);
	ft_strlcat(tab, s2, len + 1);
	return (tab);
}
