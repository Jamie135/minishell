/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/04/26 17:05:43 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile int	signal_flag;

//exit heredoc quand on fait ctrlD
void	heredoc_error(t_heredoc *heredoc, char *limiter, int fd)
{
	if (signal_flag == 1)
	{
		free_heredoc(heredoc, limiter, NULL, fd);
		signal_flag = 0;
		exit(2);
	}
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(heredoc->line_num[0], 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}

//recuperer la ligne de commande de heredoc et verifier si c'est un delimiteur
char	*heredoc_get_line(t_heredoc *heredoc, char *limiter, int fd)
{
	char	*line;
	char	*tmp;

	line = readline("heredoc> ");
	(heredoc->line_num[0])++;
	if (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0\
			&& ft_strlen(line) == ft_strlen(limiter))
			return (free_heredoc(heredoc, limiter, line, fd), exit(0), NULL);
		tmp = line;
		line = expend_str(heredoc->envi, tmp, heredoc->exit_value[0]);
		if (!line)
			return (message_heredoc(heredoc, "malloc", errno, &exit), NULL);
	}
	return (line);
}

//ouvrir le fichier *name et executer heredoc
void	heredoc_exec(char *limiter, char *name, t_heredoc *heredoc)
{
	int		fd;
	char	*line;

	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (message_heredoc(heredoc, "open heredoc", errno, &exit));
	parent_child_signal(HEREDOC);
	while (!signal_flag)
	{
		line = heredoc_get_line(heredoc, limiter, fd);
		if (!line || signal_flag == 1)
		{
			if (!signal_flag)
				heredoc_error(heredoc, limiter, fd);
			break ;
		}
		ft_putendl_fd(line, fd);
		free_ptr((void **)&line);
	}
	if (signal_flag == 1)
		exit_heredoc(heredoc, limiter, line, fd);
	return (free_heredoc(heredoc, limiter, NULL, fd), exit(0));
}

//dupliquer le limiteur et recopier le nom du fichier de la liste
//fork le heredoc et attendre
int	heredoc_init(t_heredoc *heredoc, t_list *list)
{
	char	*tmp;
	char	*limiter;
	int		pid;

	limiter = ft_strdup(list->content);
	if (!limiter)
		return (malloc_err("heredoc.c (1)"), EXIT_FAILURE);
	free_ptr((void **)&list->content);
	tmp = random_string(10);
	if (!tmp)
		return (free(limiter), malloc_err("heredoc.c (2)"), EXIT_FAILURE);
	list->content = ft_strjoin("/tmp/", tmp);
	if (!list->content)
		return (free(tmp), free(limiter), malloc_err("heredoc.c (3)"), 1);
	free_ptr((void **)&tmp);
	pid = fork();
	if (pid == -1)
		return (free(tmp), free(limiter), perror("pipe heredoc"), 1);
	if (pid == 0)
		heredoc_exec(limiter, list->content, heredoc);
	else
		waitpid(pid, NULL, 0);
	return(free_ptr((void **)&limiter), EXIT_SUCCESS);
}

//attribuer les valeurs des arguments aux struct t_heredoc
//executer heredoc_init qui lance le heredoc
int	heredoc(t_list *list, t_envi *env, int *count, int *exit_value)
{
	t_heredoc	heredoc;

	heredoc.list = list;
	heredoc.envi = env;
	heredoc.line_num = count;
	heredoc.exit_value = exit_value;
	while (list)
	{
		if (list->type == REDIR && ft_strcmp(list->content, "<<\0") == 0)
		{
			if (list->next && list->next->type == FILES)
			{
				list = list->next;
				if (heredoc_init(&heredoc, list))
					return (EXIT_FAILURE);
			}
		}
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
