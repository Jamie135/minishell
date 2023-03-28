/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:34:39 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/08 00:34:39 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_print_type(int type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == OPT)
		return ("OPT");
	else if (type == ARG)
		return ("ARG");
	else if (type == VAR)
		return ("VAR");
	else if (type == REDIR)
		return ("REDIR");
	else if (type == FILES)
		return ("FILES");
	else if (type == PIPE)
		return ("PIPE");
	else
		return ("UNKNOWN");
}

void	ft_lst_print_type(t_list *lst)
{
	if (lst == NULL)
		ft_putendl_fd("(null)", 1);
	while (lst)
	{
		printf("%s | %s\n", lst->content, ft_print_type(lst->type));
		lst = lst->next;
	}
}
