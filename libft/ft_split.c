/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:52:06 by pbureera          #+#    #+#             */
/*   Updated: 2022/06/14 11:37:37 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	**free_tab(char **tab, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	num_word(char const *s, char c)
{
	size_t	num;
	size_t	i;

	i = 0;
	num = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
			if (!s[i])
				return (num);
		}
		while (!(s[i] == c) && s[i])
			i++;
		num++;
	}
	return (num);
}

static size_t	len_word(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] && !(s[i] == c))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*dup_word(const char *s, size_t len)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = (char **)malloc(sizeof(char *) * (num_word(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < num_word(s, c))
	{
		if (!(s[i] == c) && s[i])
		{
			tab[j] = dup_word(&s[i], len_word(&s[i], c));
			if (!tab)
				return (free_tab(tab, j));
			i += len_word(&s[i], c);
			j++;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}
