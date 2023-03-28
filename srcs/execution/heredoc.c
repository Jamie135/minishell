/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:02:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/27 17:31:30 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ouvrir le fichier *name et executer heredoc
void	heredoc_exec(t_heredoc *heredoc, char *limiter, char *name)
{
	int		fd;
	char	*line;
	int		signal;

	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (message_heredoc(heredoc, "open heredoc", errno, &exit));
	signal = 0;
	while (!signal)
	{
		/* code */
	}
	
}

//determiner le limiteur et recopier le nom du fichier depuis la liste
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
}

//attribuer les valeurs des arguments aux struct t_heredoc
//executer heredoc avec heredoc_init
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
		list->next;
	}
	return (EXIT_SUCCESS);
}
