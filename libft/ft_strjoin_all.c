/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:37:28 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/08 00:37:28 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_all(char **strs, char c)
{
	char	*str;
	int		i;
	size_t	j;
	size_t	k;
	size_t	len;

	i = 0;
	len = 0;
	while (strs[i])
		len += ft_strlen(strs[i++]) + 1;
	str = malloc(sizeof(char) * (len));
	if (!str)
		return (NULL);
	i = -1;
	k = 0;
	while (strs[++i])
	{
		j = 0;
		while (strs[i][j])
			str[k++] = strs[i][j++];
		if (strs[i + 1])
			str[k++] = c;
	}
	str[k] = '\0';
	return (str);
}
