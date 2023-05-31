/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:56:25 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/26 16:58:34 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// extern volatile int	g_signal;

//exit heredoc quand on fait ctrlC
void	exit_heredoc(t_heredoc *heredoc, char *limiter, char *line, int fd)
{
	free_heredoc(heredoc, limiter, line, fd);
	exit(130);
}

// printf("g_signal: %i\n", g_signal);

//enlever les fichiers de heredoc
void	heredoc_unlink(t_list *list)
{
	while (list)
	{
		if (list->type == REDIR && ft_strcmp(list->content, "<<\0") == 0)
		{
			if (list->next)
			{
				list = list->next;
				unlink(list->content);
			}
		}
		if (list)
			list = list->next;
	}
}

//rendre le caractere c affichable si besoin  
static int	char_mod(int c)
{
	if (c < 0)
		c = -c;
	while (c > 122)
		c -= 26;
	if (c < 32)
		c += 32;
	if (c == ' ')
		c = '_';
	if (c == '/')
		c = '_';
	if (c == '.')
		c = '_';
	if (c == '$')
		c = '_';
	return (c);
}

//malloc un string aleatoire de taille len
//le string sera lu depuis fd
char	*random_string(int len)
{
	char	*buffer;
	int		fd;
	int		i;

	buffer = ft_calloc(len + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, buffer, len) == -1)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buffer[i] = char_mod(buffer[i]);
		i++;
	}
	close(fd);
	return (buffer);
}
