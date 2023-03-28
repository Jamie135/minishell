/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:12:32 by pbureera          #+#    #+#             */
/*   Updated: 2022/10/18 23:12:32 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	if (ft_putstr_fd(s, fd))
		return (EXIT_FAILURE);
	if (ft_putchar_fd('\n', fd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
