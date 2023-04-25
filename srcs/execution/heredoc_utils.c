/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:56:25 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/27 16:56:41 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_heredoc(t_heredoc *heredoc, char *limiter, char *line, int fd)
{
	free_heredoc(heredoc, limiter, line, fd);
	exit(130);
}

void	heredoc_error(t_heredoc *heredoc, char *limiter)
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(heredoc->line_num[0], 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
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

int	gnl(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

