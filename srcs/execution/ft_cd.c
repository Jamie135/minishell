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
	t_envi	*envi;
	char	*repertoire_actuel;

	envi = shell->envi;
	repertoire_actuel = getcwd(NULL, 0);
	if (!repertoire_actuel)
	{
		while (envi)
		{
			if (identique("PWD", (envi->ve)))
				repertoire_actuel = envi->value;
			envi = envi->next;
		}
		if (!repertoire_actuel)
			return (NULL);
		return (repertoire_actuel);
	}
	return (repertoire_actuel);
}

int	tilde_chemin(t_shell *shell, const char *arg)
{
	char	*home;
	char	*nouvelarg;
	char	*u;

	u = (char *)arg;
	u++;
	home = find_value_envi("HOME", shell->envi);
	nouvelarg = ft_strjoin(home, u);
	if (ft_cd_go_to(shell, nouvelarg))
		return (free(nouvelarg), EXIT_FAILURE);
	return (free(nouvelarg), EXIT_SUCCESS);
}

int	ft_cd(t_shell *shell)
{
	const char	**args = (const char **)shell->args[shell->cid];

	if (len_array(shell->args[shell->cid]) > 2)
		return (message_builtins("cd", NULL, TOOMANY), 1);
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (ft_cd_home(shell))
			return (EXIT_FAILURE);
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		if (ft_cd_back(shell))
			return (EXIT_FAILURE);
	}
	else if (args[1][0]=='~')
	{
		if (tilde_chemin(shell, args[1]))
			return (EXIT_FAILURE);
	}
	else
	{
		if (ft_cd_go_to(shell, args[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// char	*pwd_avant_cd(t_shell *shell)
// {
// 	t_envi	*envi;
// 	char	*repertoire_actuel;

// 	envi = shell->envi;
// 	repertoire_actuel = getcwd(NULL, 0);
// 	if (!repertoire_actuel)
// 	{
// 		while (envi)
// 		{
// 			if (identique("PWD", (envi->ve)))
// 				repertoire_actuel = envi->value;
// 			envi = envi->next;
// 		}
// 		if (!repertoire_actuel)
// 			return (free_pwd(shell, NULL, errno, &exit), NULL);
// 		return (repertoire_actuel);
// 	}
// 	return (repertoire_actuel);
// }

// char	*valeur_de_home(t_shell *shell)
// {
// 	t_envi	*envi;

// 	envi = shell->envi;
// 	if (envi == NULL)
// 		return (NULL);
// 	while (envi)
// 	{
// 		if (identique("HOME", (envi->ve)))
// 			return (envi->value);
// 		envi = envi->next;
// 	}
// 	return (NULL);
// }

// char	*valeur_de_oldpwd(t_shell *shell)
// {
// 	t_envi	*envi;

// 	envi = shell->envi;
// 	if (envi == NULL)
// 		return (NULL);
// 	while (envi)
// 	{
// 		if (identique("OLDPWD", (envi->ve)))
// 			return (envi->value);
// 		envi = envi->next;
// 	}
// 	return (NULL);
// }

// int	execute_tilde_et_moins(const char **arg, t_shell *shell)
// {
// 	if (!arg[0])
// 		return (0);
// 	if (arg[0][0] == '~' && arg[0][1] == '\0')
// 	{
// 		if (!valeur_de_home(shell))
// 			printf("cd: HOME not set\n");
// 		else
// 			chdir(valeur_de_home(shell));
// 		return (1);
// 	}
// 	if (arg[0][0] == '-' && arg[0][1] == '\0')
// 	{
// 		if (!valeur_de_oldpwd(shell))
// 			printf("cd: OLDPWD not set\n");
// 		else
// 		{
// 			printf("%s\n", valeur_de_oldpwd(shell));
// 			chdir(valeur_de_oldpwd(shell));
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_cd(t_shell *shell)
// {
// 	const char	**arg = (const char **)shell->args[shell->cid];
// 	char		*ancien_chemin;
// 	int			erreur;
// 	int			tilde_et_moins;

// 	arg++;
// 	erreur = 0;
// 	ancien_chemin = pwd_avant_cd(shell);
// 	tilde_et_moins = execute_tilde_et_moins(arg, shell);
// 	if (!arg || !arg[0])
// 	{
// 		if (!valeur_de_home(shell))
// 			printf("cd: HOME not set\n");
// 		chdir(valeur_de_home(shell));
// 	}
// 	else if (arg[1])
// 	{
// 		message_builtins("cd", NULL, TOOMANY);
// 		return (EXIT_FAILURE);
// 	}
// 	else if (!tilde_et_moins)
// 		erreur = chdir(arg[0]);
// 	if (erreur == -1)
// 		return (msgexit(NULL, "cd", errno, NULL), EXIT_FAILURE);
// 	return (met_a_jour_oldpwd(shell, ancien_chemin), EXIT_SUCCESS);
// }
