/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:54:21 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 14:47:07 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifier les double quotes dans un single quote
int	valid_single(char *str, bool *single_quote, bool *double_quote, int *i)
{
	if (*single_quote == true)
		*single_quote = false;
	else
		*single_quote = true;
	while (str[*i] && str[*i] != '\'')
	{
		if (str[*i] == '\"')
		{
			if (*double_quote == true)
				*double_quote = false;
			else
				*double_quote = true;
		}
		(*i)++;
	}
	if (!str[*i] && (*single_quote == true || *single_quote == true))
		return (-1);
	else
	{
		if (*single_quote == false)
			*single_quote = true;
		else
			*single_quote = false;
	}
	return (0);
}

// verifier les single quotes dans un double quote
int	valid_double(char *str, bool *single_quote, bool *double_quote, int *i)
{
	if (*double_quote == false)
				*double_quote = true;
	else
		*double_quote = false;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '\'')
		{
			if (*single_quote == true)
				*double_quote = false;
			else
				*single_quote = true;
		}
		(*i)++;
	}
	if (!str[*i] && (*single_quote == true || *single_quote == true))
		return (-1);
	else
	{
		if (*single_quote == false)
			*single_quote = true;
		else
			*single_quote = false;
	}
	return (0);
}

// verifier les quotes
int	valid_quote(char *str)
{
	int		i;
	bool	single_quote;
	bool	double_quote;

	i = -1;
	single_quote = false;
	double_quote = false;
	while (str[++i])
	{
		if (str[i] == '\'')
			if (valid_single(str, &single_quote, &double_quote, &i) == -1)
				return (-1);
		if (str[i] == '\"')
			if (valid_double(str, &single_quote, &double_quote, &i) == -1)
				return (-1);		
	}
	if (valid_open(str) == -1)
		return (-1);
	return (0);
}

char	*single_quote(char *str, int index)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	while (str[++i] && i < index)
		new[i] = str[i];
	while (str[i + j])
	{
		if (str[i + j] == '\'' && j != 2)
			j++;
		else
		{
			new[i] = str[i + j];
			i++;
		}
	}
	new[i] = '\0';
	free_ptr((void **)&str);
	return (new);
}

char	*double_quote(char *str, int index)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	while (str[++i] && i < index)
		new[i] = str[i];
	while (str[i + j])
	{
		if (str[i + j] == '\"' && j != 2)
			j++;
		else
		{
			new[i] = str[i + j];
			i++;
		}
	}
	new[i] = '\0';
	free(str);
	return (new);
}
