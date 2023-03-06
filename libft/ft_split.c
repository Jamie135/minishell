/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:12:57 by pbureera          #+#    #+#             */
/*   Updated: 2022/10/18 23:12:57 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_str(char const *s, char c)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	if (!s[0])
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nbr++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nbr++;
	return (nbr);
}

static void	next_str(char **str, size_t *len, char c)
{
	size_t	i;

	*str += *len;
	*len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

static char	**free_malloc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	size_t	len;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (find_str(s, c) + 1));
	if (!tab)
		return (NULL);
	str = (char *)s;
	len = 0;
	while (++i < find_str(s, c))
	{
		next_str(&str, &len, c);
		tab[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!tab[i])
			return (free_malloc(tab));
		ft_strlcpy(tab[i], str, len + 1);
	}
	tab[i] = NULL;
	return (tab);
}
