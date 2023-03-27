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
	fd = open("/dev/random/", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, buffer, len) == -1);
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
