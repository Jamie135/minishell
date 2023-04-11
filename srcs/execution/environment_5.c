/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:05:16 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/11 19:05:16 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//retourner la valeur de PATH dans envi
char	**get_path(t_shell *shell)
{
	char	**path;
	char	*tmp;

	tmp = find_value_envi("PATH", shell->envi);
	if (!tmp)
		return (message_free_exit(shell, NULL, PATH, &exit), NULL);
	path = ft_split(tmp, ':');
	if (!path)
		return (message_free_exit(shell, NULL, MALLOC, &exit), NULL);
	return (path);
}

//verifier si la commande est present et executable
char	*get_access(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!tmp)
			return (NULL);
		errno = 0;
		if (access(tmp, X_OK) != -1)
			return (tmp);
		free(tmp);
		i++;
	}
	return (ERROR);
}
