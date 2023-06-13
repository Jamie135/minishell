/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:30:50 by pbureera          #+#    #+#             */
/*   Updated: 2023/06/13 11:46:12 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd_update_oldpwd(t_shell *shell, char *oldpwd, int flag)
{
	char	*str;
	t_envi	*new;

	if (find_value_envi("OLDPWD", shell->envi))
	{
		update_value_envi("OLDPWD", oldpwd, VALID, shell->envi);
		if (!flag)
			free(oldpwd);
	}
	else
	{
		str = ft_strdup("OLDPWD");
		if (!str)
			return (free(oldpwd), msgexit(NULL, "cd", errno, NULL), 1);
		new = cpy_struct_envi(str, oldpwd, VALID);
		if (!new)
			return (free(oldpwd), msgexit(NULL, "cd", errno, NULL), 1);
		add_back_envi(&shell->envi, new);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd_update_pwd(t_shell *shell, char *pwd)
{
	char	*str;
	t_envi	*new;

	if (find_value_envi("PWD", shell->envi))
	{
		update_value_envi("PWD", pwd, VALID, shell->envi);
		free(pwd);
	}
	else
	{
		str = ft_strdup("PWD");
		if (!str)
			return (free(pwd), msgexit(NULL, "cd", errno, NULL), 1);
		new = cpy_struct_envi(str, pwd, VALID);
		if (!new)
			return (free(pwd), msgexit(NULL, "cd", errno, NULL), 1);
		add_back_envi(&shell->envi, new);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd_home(t_shell *shell)
{
	char	*oldpwd;
	char	*pwd;
	int		flag;

	flag = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		oldpwd = find_value_envi("PWD", shell->envi);
		if (!oldpwd)
			return (msgexit(NULL, "ft_cd (28)", errno, NULL), 1);
		flag = 1;
	}
	if (!find_value_envi("HOME", shell->envi))
		return (free(oldpwd), message_builtins("cd", NULL, HOME), 1);
	if (chdir(find_value_envi("HOME", shell->envi)))
		return (free(oldpwd), msgexit(NULL, "cd", errno, NULL), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), msgexit(NULL, "cd", errno, NULL), 1);
	if (ft_cd_update_oldpwd(shell, oldpwd, flag))
		return (free(pwd), EXIT_FAILURE);
	if (ft_cd_update_pwd(shell, pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd_back(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;
	int		flag;

	flag = 0;
	if (find_value_envi("OLDPWD", shell->envi) == NULL)
		return (message_builtins("cd", NULL, OLDPWD), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		oldpwd = find_value_envi("PWD", shell->envi);
		if (!oldpwd)
			return (msgexit(NULL, "cd", errno, NULL), 1);
		flag = 1;
	}
	if (chdir(find_value_envi("OLDPWD", shell->envi)))
		return (msgexit(NULL, "cd", errno, NULL), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), msgexit(NULL, "cd", errno, NULL), 1);
	ft_putendl_fd(pwd, STDOUT);
	if (ft_cd_back_2(shell, oldpwd, pwd, flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd_go_to(t_shell *shell, const char *arg)
{
	char	*pwd;
	char	*oldpwd;
	int		flag;

	flag = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		oldpwd = find_value_envi("PWD", shell->envi);
		if (!oldpwd)
			return (msgexit(NULL, "cd", errno, NULL), 1);
		flag = 1;
	}
	if (chdir(arg))
	{
		if (!flag)
			free(oldpwd);
		return (message_builtins("cd", (char *)arg, strerror(errno)), 1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), msgexit(NULL, "cd", errno, NULL), 1);
	if (ft_cd_update_oldpwd(shell, oldpwd, flag))
		return (free(pwd), EXIT_FAILURE);
	if (ft_cd_update_pwd(shell, pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// int	check_inexistance(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == -2)
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// void	ajoute(const char *str, t_envi *envi)
// {
// 	char	*oldpwd;
// 	t_envi	*cpy;

// 	oldpwd = malloc(7);
// 	oldpwd[0] = 'O';
// 	oldpwd[1] = 'L';
// 	oldpwd[2] = 'D';
// 	oldpwd[3] = 'P';
// 	oldpwd[4] = 'W';
// 	oldpwd[5] = 'D';
// 	oldpwd[6] = '\0';
// 	cpy = cpy_struct_envi(oldpwd, (char *)str, 0);
// 	add_back_envi(&envi, cpy);
// }

// void	met_a_jour_oldpwd(t_shell *shell, char *ancien_chemin)
// {
// 	int			trouvee;
// 	const char	**arg = (const char **)shell->args[shell->cid];
// 	t_envi		*parcours;

// 	trouvee = 0;
// 	parcours = shell->envi;
// 	while (parcours && ancien_chemin)
// 	{
// 		if (identique(parcours->ve, "OLDPWD"))
// 		{
// 			free (parcours->value);
// 			parcours->value = ancien_chemin;
// 			trouvee = 1;
// 		}
// 		if (identique(parcours->ve, "PWD"))
// 			parcours->value = pwd_avant_cd(shell);
// 		parcours = parcours->next;
// 	}
// 	if (trouvee == 0 && ancien_chemin)
// 		ajoute(ancien_chemin, shell->envi);
// }
