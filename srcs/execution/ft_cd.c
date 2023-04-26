/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:27:00 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/15 14:27:12 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ve_est_OLDPWD(char *str)
{
	if (!str)
		return (0);
	if (str[0] != 'O')
		return (0);
	if (str[1] != 'L')
		return (0);
	if (str[2] != 'D')
		return (0);
	if (str[3] != 'P')
		return (0);
	if (str[4] != 'W')
		return (0);
	if (str[5] != 'D')
		return (0);
	if (str[6] != '\0')
		return (0);
	return (1);
}

int	ve_est_HOME(char *str)
{
	if (!str)
		return (0);
	if (str[0] != 'H')
		return (0);
	if (str[1] != 'O')
		return (0);
	if (str[2] != 'M')
		return (0);
	if (str[3] != 'E')
		return (0);
	if (str[4] != '\0')
		return (0);
	return (1);
}

char	*valeur_de_HOME(t_shell *shell)
{
	t_envi	*envi;

	envi = shell->envi;
	if (envi == NULL)
		return (NULL);
	while (envi)
	{
		if (ve_est_HOME(envi->ve))
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}

char	*valeur_de_OLDPWD(t_shell *shell)
{
	t_envi	*envi;

	envi = shell->envi;
	if (envi == NULL)
		return (NULL);
	while (envi)
	{
		if (ve_est_OLDPWD(envi->ve))
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}

int	execute_tilde_et_moins(const char **arg, t_shell *shell)
{
	if (!arg[0])
		return (0);
	if (arg[0][0] == '~' && arg[0][1] == '\0')
		return(chdir(valeur_de_HOME(shell), 1);
	if (arg[0][0] == '-' && arg[0][1] == '\0')
		return(chdir(valeur_de_OLDPWD(shell)), 1);
}

int	ft_cd(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	int		erreur;
	int		tilde_et_moins;

	arg++;
	erreur = 0;
	tilde_et_moins = execute_tilde_et_moins(arg, shell);
	if (!arg || !arg[0])
	{
		if (!valeur_de_HOME(shell))
			printf("cd: HOME not set\n");
		chdir(valeur_de_HOME(shell));
	}
	else if (arg[1])
	{
		message_builtins("cd", NULL, TOOMANY);
		return (EXIT_FAILURE);
	}
	else if (!tilde_et_moins)
		erreur = chdir(arg[0]);
	if (erreur == -1)
	{
		message_free_exit(NULL, "cd", errno, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
