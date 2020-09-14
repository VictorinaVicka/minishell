/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 12:36:30 by tfarenga          #+#    #+#             */
/*   Updated: 2020/09/04 12:48:02 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include "../libs/libft/libft.h"
# include "../libs/printf/includes/ft_printf.h"
# define PROMPT "minishell"
# define LIMIT_EXPORT 40

typedef struct				s_var_splitter
{
	int						flag;
	int						as;
	int						i;
	int						j;
	int						st;
}							t_var_splitter;

typedef struct				s_var_splitter_m
{
	char					*s;
	int						cmp;
}							t_var_splitter_m;

typedef struct				s_ms
{
	void					*content;
	int						separator;
	int						space;
	struct s_ms				*next;
}							t_ms;

typedef struct				s_thread
{
	int						fd;
	char					redirect;
	char					*file;
	struct s_thread			*next;
}							t_thread;

typedef struct				s_environment
{
	char					*name;
	char					*value;
	int						exp;
	struct s_environment	*next;
}							t_environment;

typedef struct				s_terminal
{
	struct s_list			*gb_collector2;
	struct s_ms				**lst;
	char					**cmds;
	char					**envp;
	char					**av;
	char					*entry;
	char					*sep;
	int						n_cmds;
	int						i;
	int						state;
	int						code;
	t_thread				*thread;
	t_thread				*begin_thread;
	char					*buf;
	char					***split_pipe;
	int						*pipe;
	int						**pipes;
	char					**cmds_pipe;
	char					***tab_path;
	char					***args_pipe;
	int						cmd_pipe;
	int						first;
	int						unique;
	int						last;
	int						child;
	int						redir_in;
	int						redir_out;
	int						test;
	int						nb_pipe;
	int						option_n;
	int						no_arg;
	int						nb_export;
	char					*str;
	pid_t					pid;
	t_environment			*lst_env;
}							t_terminal;

void						initialization(t_terminal *data, char **envp,
											int argc, char **av);
int							print_exit(t_terminal *data);
void						safe_exit(t_terminal *data);
void						parse_input(t_terminal *data);
void						parse_commands(t_terminal *trm);
void						parse_separators(t_terminal *terminal);
void						clear_memory(t_terminal *terminal);
t_ms						*ft_lstnew_ms(const void *content, char separator,
											int flag);
void						ft_lstadd_back_ms_ls(t_ms **alst, t_ms *new);
void						ft_lstclear_ms(t_ms **lst, void (*del)(void*));
int							ft_lstsize_ms(t_ms *lst);
void						ft_print_lst(t_ms *lst);
t_ms						*ft_lstsplit_ms(char *s);
char						**ft_split_ms(char const *s, char *set, int size);
char						*get_buffer(t_terminal *data, t_ms *lst);
char						*ft_ls(char *start, char *end);
t_ms						*ft_parse_wildcard(t_ms *new, char *b);
int							ft_cmp_set_ms(char c, int *flag,
										t_ms *lst, int prev);
void						ft_lstadd_back_ms_ls(t_ms **alst, t_ms *new);
void						ft_lstadd_back_ms(t_ms **alst, t_ms *new);
void						safe_exit(t_terminal *data);
void						*add_garbage_ret(t_terminal *terminal, void **s);
char						*get_var_env(t_environment *env, char *name);
char						*get_var(t_terminal *terminal, char *b, int *inc);
char						*ft_write_args(t_terminal *terminal,
											char *b, int sep);
char						*ft_do_empty_quotes(char *s);
void						ft_parse_chev(t_ms *lst);
void						ft_error(t_terminal *terminal, int j);
int							ft_check_pipes(t_terminal *terminal);
int							is_add_var(t_ms **alst);
void						add_var(t_terminal *terminal, t_ms *lst);
int							ft_envsize(t_environment *env);
char						**parse_env(t_environment *env);
char						**parse_av(t_terminal *terminal, t_ms *lst);
char						**parse_path(t_environment *env);
int							dup_pipe(t_terminal *terminal, int nb_pipe);
int							redir(t_terminal *trm, t_ms *lst);
int							init_redir(char c, t_terminal *terminal,
										t_ms *lst, char *str);
int							init_no_redir(t_terminal *terminal);
void						exec_cmd(t_terminal *terminal, t_ms *lst);
int							ft_pipe(t_terminal *terminal,
									char **env, t_ms *lst);
void						ft_redir_pipe(t_terminal *terminal);
void						ft_error_message(t_terminal *terminal);
int							test_builtin(t_terminal *terminal);
void						ft_pwd(t_terminal *terminal);
void						ft_env(t_terminal *terminal, t_ms *lst);
int							write_redir(t_terminal *terminal);
void						ft_export_no_arg(t_terminal *terminal);
void						test_path(t_terminal *terminal, int i);
void						test_path_null(t_terminal *terminal, int i);
void						free_pipe_cmd(t_terminal *terminal);
void						ft_error(t_terminal *terminal, int j);
int							ft_exec_cmd(t_terminal *terminal, int nb_pipe,
										t_ms *lst, char **env);
int							ft_cd(t_terminal *terminal, t_ms *lst);
void						ft_exit(t_terminal *terminal, t_ms *lst);
void						ft_env(t_terminal *terminal, t_ms *lst);
void						ft_export(t_terminal *terminal, t_ms *lst);
void						ft_unset(t_terminal **trm, t_ms *lst);
void						ft_lstadd_back_env(t_environment **alst,
												t_environment *new);
int							ft_copyuntil(char **dst, char *src, char c);
void						free_pipe_cmd(t_terminal *terminal);
void						free_double_tab(char ***item, int i);
void						ft_lstadd_back_flux(t_thread **alst, t_thread *new);
void						free_thread(t_terminal *terminal);
int							ft_close(t_terminal *terminal, int nb);
int							process_pere(t_terminal *terminal,
										int nb_pipe, t_thread *begin);
void						ft_free_lst(t_ms **lst);
void						free_cmds(char **cmds);
char						*get_buffer(t_terminal *d, t_ms *lst);

#endif
