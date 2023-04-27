/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Espéranto <emploi.hebert@laposte.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:56:08 by Espéranto         #+#    #+#             */
/*   Updated: 2023/03/16 13:56:13 by Espéranto        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//check la validite du variable environnementale
static int	check_ve(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (len >= 1 && str[len - 1] == '+')
		len--;
	if (ft_all_isalnum_len(str, len) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//export la variable
static int	do_export(t_shell *shell, char *ve, char *value, int type)
{
	t_envi		*new;

	if (find_value_envi(ve, shell->envi) != NULL)
	{
		shell->envi = update_value_envi(ve, value, type, shell->envi);
		if (shell->envi == ERROR)
			return (EXIT_FAILURE);
		free(ve);
		free(value);
	}
	else
	{
		new = cpy_struct_envi(ve, value, type);
		if (!new)
			return (EXIT_FAILURE);
		add_back_envi(&(shell->envi), new);
	}
	return (EXIT_SUCCESS);
}

//affiche la valeur de export
static int	create_value(t_shell *shell, char *ve, char *value, int type)
{
	char	*tmp;
	char	*new;
	size_t	len;

	len = ft_strlen(ve);
	if (ve[len - 1] == '+')
		ve[len - 1] = '\0';
	if (find_value_envi(ve, shell->envi) != NULL)
	{
		tmp = find_value_envi(ve, shell->envi);
		new = ft_strjoin(tmp, value);
		if (!value)
			return (EXIT_FAILURE);
		free(value);
		if (do_export(shell, ve, new, type) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (do_export(shell, ve, value, type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//creer un nouveau ve
static int	create_ve(t_shell *shell, char *args)
{
	int		flag;
	char	*ve;
	char	*value;
	int		type;

	flag = false;
	type = VALID;
	if (ft_strchr(args, '=') == NULL)
		type = UNVALID;
	ve = variable_env(args);
	value = value_env(args);
	if (!ve || !value)
		return (malloc_err("export.c (109)"), EXIT_FAILURE);
	if (check_last_char(ve, '+'))
		flag = true;
	if (flag && create_value(shell, ve, value, type))
		return (free(value), free(ve), malloc_err("export.c (111)"), 1);
	else if (!flag && do_export(shell, ve, value, type))
		return (free(value), free(ve), malloc_err("export.c (115)"), 1);
	return (EXIT_SUCCESS);
}

int	ft_export(t_shell *shell)
{
	const char	**arg = (const char **)shell->args[shell->cid];
	int			k;

	k = 0;
	if (arg[1] == NULL)
		return (FAILURE);
	while (arg[++k])
	{
		if (is_special_var(arg[k][0]) || check_ve((char *)arg[k]))
		{
			printf("spe var: %i ; check_ve: %i\n", is_special_var(arg[k][0]), check_ve((char *)arg[k]));
			message_builtins("export", (char *)arg[k], ID);
			shell->mode = 1;
			continue ;
		}
		if (create_ve(shell, (char *)arg[k]))
			return (EXIT_FAILURE);
		if (shell->environment)
			free_split(shell->environment);
		shell->environment = init_env(shell->envi);
		if (shell->environment == ERROR)
			return (EXIT_FAILURE);
	}
	if (shell->mode == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
