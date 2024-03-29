/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:32:57 by pbureera          #+#    #+#             */
/*   Updated: 2023/05/23 12:39:52 by pbureera         ###   ########.fr       */
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

# define MINISHELL 0
# define PARENT 1
# define CHILD 2
# define HEREDOC 3

# define SYNTAX_ERR "syntax error near unexpected token"

typedef struct s_free
{
	int		status;
	char	**split;
	bool	*unexpended;
	bool	*quoted;
}	t_free;

typedef struct s_expand
{
	char	*result;
	int		i;
}	t_expand;

int			run(char **envp, char *line, t_list *list, t_free *free_var);
t_envi		*init_environment(char **envp);
/* list.c */
t_list		*fill_list(char *line, t_free *free_var, t_envi *env, \
						int *exit_value);
t_list		*fill(t_list *list, t_free *free_var);
int			is_str_dot(char *line);

/* quote.c && quote_utils.c */
int			valid_quote(char *str);
int			valid_single(char *str, bool *single_quote, \
						bool *double_quote, int *i);
int			valid_double(char *str, bool *single_quote, \
						bool *double_quote, int *i);
char		*single_quote(char *str, int index);
char		*double_quote(char *str, int index);
int			valid_open(char *str);
int			is_unexpended(char *str);
int			is_quoted(char *str);
int			space_in_single_quote(char *line);
int			space_in_double_quote(char *line);

/* string.c && string_quote.c && string_utils.c */
char		*get_string(char *str, t_envi *env);
int			len_string(char *str);
static void	string_1(int *i, int *j, char *str, char *new);
static void	string_2(int *i, int *j, char *str, char *new);
char		*final_string(char *new);
int			quote_index(char *str, int index, char c);
int			single_quote_index(char *str, char *new, int i, int j);
int			double_quote_index(char *str, char *new, int i, int j);
int			new_string_single(char *new, char *str, char c);
int			new_string_double(char *new, char *str, char c);
char		*string_quote(char *str);
int			len_quote(char *str);
void		fill_quote_single_space(char *str, char *new, int *i, int *j);
void		fill_quote_double_space(char *str, char *new, int *i, int *j);
void		is_quote_next(char *str, int *i, int *len);

/* split_pipe.c */
char		*split_pipe(char *str);
int			len_pipe(char *str);
void		complete_string(char *new, int *i, int *j, char *str);
int			len_unfound(char *line);
int			dots_not_found(char *line, int *exit_value);

/* split_line.c && split_line_utils.c */
char		**split_line(char const *s, char c);
static char	**free_tab(char **tab, size_t j);
size_t		increment_single_quote(const char *s);
size_t		increment_double_quote(const char *s);
int			increment_word(const char *s, bool quote);
int			len_split(char **split);
int			valid_syntax_2(char *line, int *i);

/* trim.c && trim_utils.c */
int			trim_split(char **split, t_free *free_var);
int			trim_protect(char **split, t_free *free_var);
char		*clean_string(char *str, int tmp);
char		*strdup_free(char *str, int free_var);
void		free_all_trim(t_list *list, char **tab, char *line, char *str);
char		*trim_command(char *line);
void		spacecmd_not_found(char *line, int *exit_value);
char		*trim_unfound(char *line);

/* expend_parsing.c */
int			expend_pars(t_free *free_var, t_envi *env, int exit_value);
char		*space_str(char *str);
int			len_space_str(char *str);
char		*command_in_quoted(char *line);
int			unfound_command(char *line, int *exit_value);
char		*expand(char *str, t_envi *env);
void		expand_base(t_expand *exp, char *str, t_envi *env);
void		expand_found_quote(t_expand *exp, char *str);
void		expand_found_dollar(t_expand *exp, char *str, t_envi *env);
void		expand_env(char *str, t_expand *exp, int j, t_envi *env);
char		*cpy_env_line(char *to_find, t_envi *env);
int			ft_isset(char c, char const *set);

/* type.c */
void		type(t_list *list);
int			get_type(char *str, int last_type);
int			get_type_redir(char *str);
int			line_user(char *line, int *exit);
void		cmd_unfound(char *line);

/* free_parsing_1.c && free_parsing_2.c */
void		*free_quote(char *str, int *exit);
void		free_line_and_split(char *line, char **split);
int			free_null_list(t_list *list, t_free *free_var, char *line, \
							t_envi *env);
void		*free_fill(char **tab, t_list *list, char *str);
int			free_trim(t_free *free_var, int i);
void		*free_split_index(char **split, int index, int message);
void		free_split_parsing(char **split);
void		free_var_all(t_free	*free_var);

/* inside_quote.c */
int			is_str_alnum_dollars(char *str);
int			is_inside_closed(char *line);
char		*trim_inside(char *line);

/* utils_parsing*/
int			valid_syntax(char *line, int *exit_value);
void		fill_inc(char *str, char *new, int *i, int j);
void		fill_quote_inc(char *str, char *new, int *i, int j);
int			dollars_pars(char *str, int *exit);
int			find_spe_var(char *str);
int			dollar_special_var(char c);
char		*trim_single(char *line);
char		*trim_double(char *line);
char		*trim_inside(char *line);
int			only_quotes(char *line, int *exit_value);
int			find_end_quote(char *str, char c, int start);
char		*join_character(char *str, char c);
char		*replace_by_variable(char *src, int start, int end, t_envi *env);
char		*cpy_var(char *src, int start, int end);

/* signals.c */
void		sig(void);
void		ctrlc(int signum);
int			parent_child_signal(int pro);

void		ft_exit(t_list *list, t_envi *envi, char *line, t_free *free_var);

#endif
