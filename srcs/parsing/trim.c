/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:46:11 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/20 15:28:45 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//enlever les quotes (retourner le string sans les guillemets)
char	*clean_string(char *str, int tmp)
{
	int		i;
	char	*new;

	i = -1;
	new = strdup_free(str, 0);
	if (!new)
		return (NULL);
	while (new[++i] && (size_t)i < ft_strlen(new))
	{
		if (new[i] == '\'')
		{
			tmp = i;
			i = quote_index(new, i, '\'') - 2;
			new = strdup_free(single_quote(new, tmp), 1);
		}
		else if (new[i] == '\"')
		{
			tmp = i;
			i = quote_index(new, i, '\"') - 2;
			new = strdup_free(double_quote(new, tmp), 1);
		}
		if (!new)
			return (NULL);
	}
	return (new);
}

//malloc les variables de la struct t_free
//free_var->split represente la liste de commande trimmer
//free->var->quoted represente un tableau booleen dont chaque
//           indice i contient la valeur booleenne de split[i]
int	trim_protect(char **split, t_free *free_var)
{
	free_var->split = malloc(sizeof(char *) * (len_split(split) + 1));
	if (!free_var->split)
		return (-1);
	free_var->unexpended = ft_calloc(sizeof(char *), (len_split(split) + 1));
	if (!free_var->unexpended)
	{
		free_split(split);
		return (-1);
	}
	free_var->quoted = ft_calloc(sizeof(char *), (len_split(split) + 1));
	if (!free_var->quoted)
	{
		free(free_var->unexpended);
		free(free_var->quoted);
		free_split(split);
		return (-1);
	}
	return (0);
}

//initialiser les variables de la struct t_free: split, unexpended et quoted
//trim la liste de commande obtenu par split_line(str, ' ')
//i.e. on enleve les quotes et les espaces en trop
int	trim_split(char **split, t_free *free_var)
{
	int		i;
	int		tmp;

	if (trim_protect(split, free_var) == -1)
		return (-1);
	i = -1;
	while (split[++i])
	{
		tmp = 0;
		free_var->split[i] = clean_string(split[i], tmp);
		if (!free_var->split[i])
			return (free_trim(free_var, i));
		if (ft_strcmp(free_var->split[i], split[i])
			&& is_unexpended(split[i]))
			free_var->unexpended[i] = true;
		if (is_quoted(split[i]))
			free_var->quoted[i] = true;
	}
	free_var->split[i++] = NULL;
	free_split_parsing(split);
	return (0);
}
