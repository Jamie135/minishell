/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:46:54 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/29 14:37:18 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pid_return(int mode)
{
	if (mode == 130)
		ft_putchar_fd('\n', STDERR);
	else if (mode == 131)
		ft_putendl_fd("Quit (core dumped)", STDERR);
	else
		return ;
}

//retourner le len de **args 
int	len_array(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

//verifier si str est composer uniquement de caractere alphanumerique
int	is_str_alnum(char *str)
{
	size_t	i;
	size_t	n;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			n++;
		i++;
	}
	if (n == len)
		return (1);
	return (0);
}
