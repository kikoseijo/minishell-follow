/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:44:32 by albaur            #+#    #+#             */
/*   Updated: 2022/07/26 15:27:14 by albaur           ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft.h"
# include "ft_fprintf.h"
# include "_functions.h"
# include "tok_stacks.h"

# define ENV_FILE "/tmp/minishell_env"
# define TMP_FILE "/tmp/temporary"

// main struct
typedef struct s_data
{
	int			exit;
	char		*input;
	char		*prompt;
	int			shlvl;
	char		*tmp;
}				t_data;

// other structs

typedef struct s_check
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		squote;
	int		dquote;
	char	**split;
}				t_check;

typedef struct s_read
{
	ssize_t	i;
	int		fd;
	char	buffer[2];
	char	*tmp;
	char	**env;
}				t_read;

typedef struct s_delete
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**ptr;
	char	**new;
}				t_delete;

typedef struct s_export
{
	int		i;
	ssize_t	j;
	char	*tmp;
	char	**env;
	char	**input;
}				t_export;

typedef struct s_dollar
{
	char	*line;
	char	*str;
	char	*varname;
	char	*var;
	ssize_t	line_len;
	ssize_t	len;
	ssize_t	varname_len;
	ssize_t	var_len;
	ssize_t	i;
	ssize_t	j;
	int		sq;
	int		dq;
}				t_dollar;

typedef struct s_var
{
	pid_t	pid;
	int		fd[2];
	int		**pipes;
	int		status;
	int		ac;
	char	**av;
	int		mode;
	int		type;
	size_t	stack_len;
}			t_var;

typedef struct s_searcher
{
	char	**paths;
	char	*exec_path;
	char	*env_path;
	char	**cmd_args;
	char	*append;
	size_t	i;
}			t_searcher;

typedef struct s_redir
{
	int	mode;
	int	type;
	int	fd;
}			t_redir;

typedef struct s_exec
{
	int		i;
	char	*cmd;
	char	**env;
}			t_exec;

typedef struct s_hd
{
	char	**arr;
	char	*buffer;
	char	*temp;
	int		cmp;
	int		bytes_read;
	int		done;
}				t_hd;

typedef struct s_exit
{
	int		shlvl;
	int		ret;
	char	*tmp;
	char	*err;
	char	*str;
}				t_exit;

// init
int			init_shell(t_data *data);
int			init_mode(int n);

// sanity check
int			ft_check_quotes(char *str);

// tokenizing
t_token		*ft_token_creator(char *line, size_t line_index);
void		ft_tokenizer(char **arr);
void		ft_tokdisplay(t_token *token);
void		ft_tokdel(t_token *tok);
size_t		ft_tokstrlen(t_token *token);
int			ft_tokcmp(t_token *token, int type);

void		ms_dollar_manager(t_stack *stack);
void		ms_dollar_parser(t_token *token, ssize_t *index);
void		ms_dollar_quote_eraser(t_stack *stack);
void		ms_dollar_counter(t_dollar *dollar, ssize_t *index);
char		*ms_dollar_replacer(t_dollar *dollar);
ssize_t		ms_dollar_checker(t_token *token);
int			ms_usd_quote_checker(t_token *token, ssize_t *index);
int			ms_dollar_check_charset(char c);
void		ft_usd_quote_counter(char *str, size_t *i, size_t *counter,
				char quote);
size_t		ft_usd_quote_len(char *str);

// parsing
void		process_input(t_data *data);
char		**ms_split(char *s);
size_t		ms_let_count(char *str, size_t *index);
int			ms_check_charset(char c);
int			between_squotes(char *str, size_t *index);
int			squote_len_index(char *str, size_t *index);
char		*ft_squote_pruner_index(char *quote, char *str,
				size_t *index, size_t *j);
int			between_dquotes(char *str, size_t *index);
int			dquote_len_index(char *str, size_t *index);
char		*ft_dquote_pruner_index(char *quote, char *str,
				size_t *index, size_t *j);
int			ft_isoper(char c);
int			oper_len_index(char *str, size_t *index);
char		*ft_oper_writer_index(char *quote, char *str,
				size_t *index, size_t *j);
int			ft_parser(t_stack *stack);

// env
char		*ft_getenv(char *varname);
char		*env_get(char *name, char **env);
char		*env_get_arg(char *var);
char		*env_get_pwd(void);
int			env_get_shlvl(void);
void		env_write(char *path, char **env);
void		env_set(char *str, char *value, char ***env);
void		env_set_arg(char *var, char *value);
char		**env_add(char *str, char ***env);
char		**env_delete(char *str, char ***env);
char		*env_get(char *str, char **env);
ssize_t		env_search(char *str, char **env);
char		**env_read(char *path);

// builtins
int			builtin_launch(char **cmd_args);
int			builtin_pwd(char **str);
int			builtin_cd(char **path);
void		builtin_cd_chdir(void);
int			builtin_export(char **str);
int			builtin_unset(char **str);
int			builtin_env(char **str);
int			builtin_exit(char **str);
int			builtin_echo(char **av);

// signals
void		sig_ignore(int sig);
void		sig_wait(int sig, void (*hdlr)(int, siginfo_t *, void *));
void		sig_handler(int sig, siginfo_t *info, void *context);
void		sig_toggle(int n);
void		sig_int_nl(int sig, siginfo_t *info, void *context);
void		sig_handler(int sig, siginfo_t *info, void *context);
void		here_doc_sig_handler(int sig, siginfo_t *info, void *context);

// pipex
void		pipex(t_stack **stack, size_t i, t_var *var);
int			pipex_open(t_stack **stack, size_t i, t_var *var);
int			pipex_close(t_stack **stack, size_t i, t_var *var);
void		pipex_pipes(size_t len, t_var *var);
int			child_process(t_stack **stack, size_t i, t_var *var);
void		child_process_exit(int code);
t_var		get_args(char ac, char *av[]);
int			ft_exec(char **cmd_args, t_var *var);
void		ft_exec_error(int i, char **cmd_args);
int			ft_exec_min(char *cmd);
char		**ft_exec_args(char **cmd_args);
char		*ft_path_searcher(char *cmd);
int			ft_self_searcher(char **env, char **cmd_args);
size_t		pipe_counter(t_stack *stack);
int			pipe_manager(t_stack *stack);
t_stack		**ft_stack_splitter(t_stack *stack);
char		**ft_lst_to_arr(t_stack *stack);
char		*ft_lst_to_arrdup(t_token *token);
int			ft_redir_parser(t_stack *av, t_var *var);
int			here_doc_redir_fd(t_stack **av, t_var *var);
void		ft_hd_performer(char *path, t_hd *hd);
void		tilde_replacer(char **path);
int			tilde_searcher(char	**path);
void		check_ms_launch(t_stack *stack);
void		set_last_input(char **args);

// utils
char		*ft_concat(char *s1, char *s2);
void		throw_error(t_data *data, char *msg, int err);
int			ret_err(char *str, char *str2, int i);
void		ret_null(char *str, char *str2);
void		ft_stacktab_clear(t_stack **tab);
void		ft_stack_freer(t_stack *stack);

#endif