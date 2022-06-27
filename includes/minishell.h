/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:44:32 by albaur            #+#    #+#             */
/*   Updated: 2022/06/27 18:15:43 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# include "_functions.h"
# include "tok_stacks.h"

# define ENV_FILE "/tmp/minishell_env"

// main struct
typedef struct s_data
{
	int			exit;
	int			mode;
	char		*input;
}		t_data;

// other structs

typedef struct s_check
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		squote;
	int		dquote;
	char	**split;
}		t_check;

typedef struct	s_read
{
	ssize_t	i;
	int		fd;
	char	buffer[2];
	char	*tmp;
	char	**env;
}		t_read;

// init
int			init_shell(t_data *data);
int			init_env(void);

// sanity check
int			check_quotes(t_data *data);
int			check_quotes_end(int *str);
void		check_quotes_count(char *str, int *squote, int *dquote);

// token
t_token		*ft_token_creator(char *line, size_t line_index);
t_stack		*ft_tokenizer(char *arr[]);

// parsing
void		process_input(t_data *data);
int			ms_check_charset(char c);
int			quote_checker(char *line);
char		**ms_split(char *s);
int			between_squotes(char *str, size_t *index);
int			squote_len_index(char *str, size_t *index);
char		*ft_squote_pruner_index(char *quote, char *str, size_t *index, size_t *j);
int			between_dquotes(char *str, size_t *index);
int			dquote_len_index(char *str, size_t *index);
char		*ft_dquote_pruner_index(char *quote, char *str, size_t *index, size_t *j);
char		*env_get_pwd(void);
int			ft_isoper(char c);
int			oper_len_index(char *str, size_t *index);
char		*ft_oper_writer_index(char *quote, char *str, size_t *index, size_t *j);

// env
char		*env_get(char *name, char **env);
void		env_write(char *path, char **env);
void		env_set(char *str, char *value, char ***env);
char		**env_add(char *str, char ***env);
char		*env_get(char *str, char **env);
ssize_t		env_search(char *str, char **env);
char		**env_read(char *path);

// builtins
void		pwd(void);
void		cd(char	*path);
void		export(char *str);

// signals
void		sig_ignore(t_data *data, int sig);
void		sig_wait(t_data *data, int sig,
				void (*hdlr)(int, siginfo_t *, void *));
void		sig_handler(int sig, siginfo_t *info, void *context);

// utils
void		throw_error(t_data *data, char *msg, int err);
char		**ft_arrdup(char **arr);
size_t		ft_arrlen(char **array);

#endif