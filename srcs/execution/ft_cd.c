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

void    ajoute(const char *str, t_envi *envi)
{
        while (envi->next)
                envi = envi->next;
        envi->ve = avant_egal(str);
        envi->value = apres_egal(str);
        envi->next = NULL;
}

void    met_a_jour_OLDPWD(t_shell *shell, char *ancien_chemin)
{
        int                     trouvee;
        const char      **arg = (const char **)shell->args[shell->cid];
        t_envi          *parcours;


        trouvee = 0;
        parcours = shell->envi;
        while (parcours)
        {
                if (identique(parcours->ve, "OLDPWD"))
                {
                        parcours->value = ancien_chemin;
                        trouvee = 1;
                }
        parcours = parcours->next;
        }
}

char    *pwd_avant_CD(t_shell *shell)
{
        char    *repertoire_actuel;

        repertoire_actuel = getcwd(NULL, 0);
        if (!(repertoire_actuel))
                return (message_free_exit(shell, NULL, errno, &exit), NULL);
        return (repertoire_actuel);
}

char	*valeur_de_HOME(t_shell *shell)
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

char	*valeur_de_OLDPWD(t_shell *shell)
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
		if (!valeur_de_HOME(shell))
			printf("cd: HOME not set\n");
		return(chdir(valeur_de_HOME(shell), 1);
	}
	if (arg[0][0] == '-' && arg[0][1] == '\0')
	{
		if (!valeur_de_OLDPWD(shell))
			printf("cd: OLDPWD not set\n");
		return(chdir(valeur_de_OLDPWD(shell)), 1);
	}
	return (0);
}

int	ft_cd(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	char            *ancien_chemin;
	int		erreur;
	int		tilde_et_moins;

	arg++;
	erreur = 0;
	ancien_chemin = pwd_avant_CD(shell);
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
	met_a_jour_OLDPWD(shell, ancien_chemin);
	return (EXIT_SUCCESS);
}
