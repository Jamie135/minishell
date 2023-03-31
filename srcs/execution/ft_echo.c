/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:33:27 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/14 15:33:40 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_envi
{
	char	*ve;
	char	*value;
}	t_envi;

// retourne 1 si il y a l'option n retourne 0 sinon
static int	option_n(char *str)
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

static int	cherche_premier_argument(char **arg)
{
	int	k;

	k = 0;
	while (arg[k] && option_n(arg[k]))
		k++;
	return (k);
}

void	ecrit(char **arg, int k, int option)
{
	while (arg[k])
	{
		if (option == 0)
			printf("%s", arg[k]);
		if (option == 1 && arg[k][0] != '\0')
			printf("%s", arg[k]);
		k++;
		if (arg[k])
			printf(" ");
	}
	if (option == 0)
		printf("\n");
}

// option == 1 si -n option == 0 si pas -n
void	ft_echo(t_envi *envi, char **arg)
{
	int	option;
	int	k;

	(void)envi;
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
			return ;
		}
		if (option == 1)
			return ;
	}
	ecrit(arg, k, option);
}
// MAIN DE TEST A SUPPRIMER

int	main(int ac, char **av)
{
	char	**argu;

	(void)ac;
	argu = av;
	argu++;
	ft_echo(NULL, argu);
}
