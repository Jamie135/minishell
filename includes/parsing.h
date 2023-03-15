/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:32:57 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/14 17:23:33 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "parsing.h"
# include "execution.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

typedef struct s_free
{
	char	**split;
	bool	not_expend;
	bool	*is_in_quote;
}	t_free;

/* list.c */
t_list		*fill_list(char *str, t_free *to_free);

/* quote.c */
int			valid_quote(char *str);
int			valid_single(char *str, int *single_quote, int *double_quote, int *i);
int			valid_double(char *str, int *single_quote, int *double_quote, int *i);
int			valid_open(char *str);

/* string.c */
char		*get_string(char *str);
int			len_string(char *str);
static void	string_1(int *i, int *j, char *str, char *new);
static void	string_2(int *i, int *j, char *str, char *new);
char		*final_string(char *new);

/* string_utils.c */
int			quote_index(char *str, int index, char c);
int			single_quote_index(char *str, char *new, int i, int j);
int			double_quote_index(char *str, char *new, int i, int j);
int			new_string_single(char *new, char *str, char c);
int			new_string_double(char *new, char *str, char c);

/* split_pipe.c */
char		*split_pipe(char *str);
int			len_pipe(char *str);
void		complete_string(char *new, int *i, int *j, char *str);

/* split_string.c && split_string_utils.c */
char		**split_string(char const *s, char c);
size_t		increment_single_quote(const char *s);
size_t		increment_double_quote(const char *s);
int			increment_word(const char *s, int quote);

/* free_parsing.c */
void		*free_quote(char *str);
void		free_line_and_split(char *line, char **split);
void		free_null_list(t_list *list, t_free *to_free, char *line, t_envi *env);
static char	**free_tab(char **tab, size_t j);
void		*free_fill(char **tab, t_list *list, char *str);

/* signals.c */

#endif
