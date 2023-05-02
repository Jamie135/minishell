/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:27:00 by Espéranto         #+#    #+#             */
/*   Updated: 2023/04/28 17:31:58 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pwd_avant_cd(t_shell *shell)
{
	char	*repertoire_actuel;

	repertoire_actuel = getcwd(NULL, 0);
	if (!(repertoire_actuel))
		return (msgexit(shell, NULL, errno, &exit), NULL);
	return (repertoire_actuel);
}

char	*valeur_de_home(t_shell *shell)
{
	t_envi	*envi;

	envi = shell->envi;
	if (envi == NULL)
		return (NULL);
	while (envi)
	{
		if (identique("HOME", (envi->ve)))
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}

char	*valeur_de_oldpwd(t_shell *shell)
{
	t_envi	*envi;

	envi = shell->envi;
	if (envi == NULL)
		return (NULL);
	while (envi)
	{
		if (identique("OLDPWD", (envi->ve)))
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
	{
		if (!valeur_de_home(shell))
			printf("cd: HOME not set\n");
		return (chdir(valeur_de_home(shell)), 1);
	}
	if (arg[0][0] == '-' && arg[0][1] == '\0')
	{
		if (!valeur_de_oldpwd(shell))
			printf("cd: OLDPWD not set\n");
		else
			printf("%s\n", valeur_de_oldpwd(shell));
		return (chdir(valeur_de_oldpwd(shell)), 1);
	}
	return (0);
}

int	ft_cd(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	char		*ancien_chemin;
	int			erreur;
	int			tilde_et_moins;

	arg++;
	erreur = 0;
	ancien_chemin = pwd_avant_cd(shell);
	tilde_et_moins = execute_tilde_et_moins(arg, shell);
	if (!arg || !arg[0])
	{
		if (!valeur_de_home(shell))
			printf("cd: HOME not set\n");
		chdir(valeur_de_home(shell));
	}
	else if (arg[1])
	{
		message_builtins("cd", NULL, TOOMANY);
		return (EXIT_FAILURE);
	}
	else if (!tilde_et_moins)
		erreur = chdir(arg[0]);
	if (erreur == -1)
		return (msgexit(NULL, "cd", errno, NULL), EXIT_FAILURE);
	return (met_a_jour_oldpwd(shell, ancien_chemin), EXIT_SUCCESS);
}
