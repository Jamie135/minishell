/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:13:11 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/15 17:13:11 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envi	*init_environment(char **envp)
{
	t_envi	*envi;

	envi = NULL;
	envi = init_envi(envp);
	if (envi == NULL)
		envi = null_envi(envi);
	return (envi);
}

char	*trim_single(char *line)
{
	char	*new;
	int		i;
	int		j;
	int		flag;

	new = malloc(sizeof(char *) * (ft_strlen(line) - 1));
	if (!new)
		return (line);
	i = 0;
	j = -1;
	flag = 0;
	while (line[i++])
	{
		if (line[i] != '\'')
			new[++j] = line[i];
		else if (line[i] == '\'' && flag == 0)
			flag = 1;
		else if (line[i] == '\'' && flag == 1)
			new[++j] = line[i];
	}
	new[j] = '\0';
	return (new);
}

char	*trim_double(char *line)
{
	char	*new;
	int		i;
	int		j;
	int		flag;

	new = malloc(sizeof(char *) * (ft_strlen(line) - 1));
	if (!new)
		return (line);
	i = 0;
	j = -1;
	flag = 0;
	while (line[i++])
	{
		if (line[i] != '\"')
			new[++j] = line[i];
		else if (line[i] == '\"' && flag == 0)
			flag = 1;
		else if (line[i] == '\"' && flag == 1)
			new[++j] = line[i];
	}
	new[j] = '\0';
	return (new);
}

int	dollar_special_var(char c)
{
	if (c == '?' || c == '#' || c == '&' || c == '\0' || c == '.' \
		|| c == ',' || c == '=' || c == '+' || c == '-' || c == '%' \
		|| c == '!' || c == '/' || c == '0' || c == ':' || c == ';' \
		|| c == '<' || c == ')' || c == '>' || c == ']' || c == '}' \
		|| c == '\\' || c == '^' || c == '_' || c == '~' || c == '{' \
		|| c == '[' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

// char	*trim_single(char *line)
// {
// 	char	*new;
// 	int		i;
// 	int		j;
// 	int		flag;

// 	new = malloc(sizeof(char *) * (ft_strlen(line) - 1));
// 	if (!new)
// 		return (line);
// 	i = 1;
// 	j = 0;
// 	flag = 0;
// 	while (line[i])
// 	{
// 		if (line[i] != '\'')
// 		{
// 			new[j] = line[i];
// 			i++;
// 			j++;
// 		}
// 		else if (line[i] == '\'' && flag == 0)
// 		{
// 			flag = 1;
// 			i++;
// 		}
// 		else if (line[i] == '\'' && flag == 1)
// 		{
// 			new[j] = line[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	new[j] = '\0';
// 	return (new);
// }

// char	*trim_double(char *line)
// {
// 	char	*new;
// 	int		i;
// 	int		j;
// 	int		flag;

// 	new = malloc(sizeof(char *) * (ft_strlen(line) - 1));
// 	if (!new)
// 		return (line);
// 	i = 1;
// 	j = 0;
// 	flag = 0;
// 	while (line[i])
// 	{
// 		if (line[i] != '\"')
// 		{
// 			new[j] = line[i];
// 			i++;
// 			j++;
// 		}
// 		else if (line[i] == '\"' && flag == 0)
// 		{
// 			flag = 1;
// 			i++;
// 		}
// 		else if (line[i] == '\"' && flag == 1)
// 		{
// 			new[j] = line[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	new[j] = '\0';
// 	return (new);
// }
