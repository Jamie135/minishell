/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:10:06 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/06 14:10:07 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include "execution.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>

int			run(char **envp, char *line, t_list *list, t_free *free_var);

#endif
