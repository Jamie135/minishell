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

char	*trim_unfound(char *line)
{
	char	*new;
	int		len;
	int		i;
	int		j;
	int		flag;

	len = len_unfound(line);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (line);
	i = -1;
	j = 0;
	flag = 0;
	while (line[++i])
	{
		if (line[i] != '\'' && line[i] != '\"' )
		{
			new[j] = line[i];
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}

void	spacecmd_not_found(char *line, int *exit_value)
{
	char	*tmp;

	tmp = space_str(line);
	if (tmp)
	{
		ft_putstr_fd(tmp, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd("command not found", STDERR);
	free(tmp);
	free(line);
	*exit_value = 127;
}

// char	*trim_command(char *line)
// {
// 	char	*new;
// 	int		i;
// 	int		flag;

// 	new = malloc(sizeof(char *) * (ft_strlen(line) - 2));
// 	if (!new)
// 		return (line);
// 	i = 1;
// 	flag = 0;
// 	while (line[i])
// 	{
// 		if (line[i] != '\'' && line[i] != '\"' )
// 			new[i] = line[i];
// 		else if ((line[i] == '\'' || line[i] == '\"') && flag == 1)
// 			new[i] = line[i];
// 		else if ((line[i] == '\'' || line[i] == '\"') && flag == 0)
// 			flag = 1;
// 		i++;
// 	}
// 	return (new);
// }

char	*trim_command(char *line)
{
	char	*tmp;

	tmp = line;
	if (tmp[0] == '\'')
		line = trim_single(line);
	else if (tmp[0] == '\"')
		line = trim_double(line);
	free(tmp);
	return (line);
}

void	free_all_trim(t_list *list, char **tab, char *line, char *str)
{
	free_list(list);
	free_split(tab);
	free(line);
	free(str);
}

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
