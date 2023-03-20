/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:11:08 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 14:20:57 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*strdup_free(char *str, int free_var)
{
	char	*s;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	i = 0;
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = 0;
	if (free_var == 1)
		free(str);
	return (s);
}
