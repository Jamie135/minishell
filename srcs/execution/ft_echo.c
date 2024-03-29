/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:33:27 by Espéranto         #+#    #+#             */
/*   Updated: 2023/05/02 15:52:37 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	write_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != -2)
	{
		if (write(STDOUT, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

// retourne 1 si il y a l'option n retourne 0 sinon
static int	option_n(const char *str)
{
	int	k;

	k = 1;
	if (str && str[0])
	{
		if (str[0] == '-')
		{
			while (str[k] == 'n')
				k++;
			if (str[k] == '\0')
				return (1);
		}
	}
	return (0);
}

static int	cherche_premier_argument(const char **arg)
{
	int	k;

	k = 0;
	while (arg[k] && option_n(arg[k]))
		k++;
	return (k);
}

void	ecrit(const char **arg, int k, int option, t_shell *shell)
{
	while (arg[k])
	{
		if (option == 0)
		{
			if (write_echo((char *)arg[k]) == -1)
				msgexit(shell, ECHO_ERR, errno, &exit);
		}
		if (option == 1 && arg[k][0] != '\0')
		{
			if (write_echo((char *)arg[k]) == -1)
				msgexit(shell, ECHO_ERR, errno, &exit);
		}
		if (arg[k + 1] && check_unknown((char *)arg[k]) != -1)
			write(STDOUT, " ", 1);
		k++;
	}
	if (option == 0)
		printf("\n");
}

// option == 1 si -n option == 0 si pas -n
int	ft_echo(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	int			option;
	int			k;

	arg++;
	(void)shell->envi;
	option = 0;
	if (arg)
		option = option_n(arg[0]);
	if (arg)
		k = cherche_premier_argument(arg);
	if (arg[k] == NULL)
	{
		if (option == 0)
		{
			printf("\n");
			return (EXIT_FAILURE);
		}
		if (option == 1)
			return (EXIT_FAILURE);
	}
	ecrit(arg, k, option, shell);
	return (EXIT_SUCCESS);
}

// int i = 0;
// while (i < len_array((char **)arg))
// {
// 	printf("arg[%i]: %s, len: %i\n", i, arg[i], (int)ft_strlen(arg[i]));
// 	i++;
// }
