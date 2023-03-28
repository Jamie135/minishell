/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:19:00 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/28 21:19:00 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//verifier si ce n'est pas un caractere special ou non affichable
int	is_special_var(char c)
{
	if (ft_isdigit(c) || c == '?' || c == '!' || c == '@' || c == '#' \
		|| c == '&' || c == '\0' || c == '=' || c == '+' || c == '-')
		return (1);
	return (0);
}

//chercher key dans l'environnement puis 
//donner et dupliquer sa valeur si on le trouve
char	*add_value_to_ve(char *ve, t_envi *envi)
{
	char	*value;

	if (find_value_envi(ve, envi) != NULL)
		value = ft_strdup(find_value_envi(ve, envi));
	else
		value = ft_strdup("\0");
	return (value);
}

//compter le nombre de '$'
size_t	count_dollar(char *str)
{
	size_t	i;
	size_t	dollar;

	i = 0;
	dollar = 0;
	while (str[i])
	{
		if (str[i] == '$')
			dollar++;
		i++;
	}
	return (dollar);
}

//ajouter un space devant les '$' et transformer les '$' en '-1'
//pour split avec -1 comme delimiteur
char	*add_space_to_dollar(char *str)
{
	size_t	dollars;
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new;

	dollars = count_dollar(str);
	len = ft_strlen(str);
	new = ft_calloc((dollars + len + 1), sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			new[j++] = -1;
		new[j++] = str[i++];
	}
	free_ptr((void **)&str);
	return (new);
}
