/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:44:36 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/07 14:24:10 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "messages.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h> 
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h> 
# include <sys/ioctl.h>
# include <sys/stat.h> 
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PWD 2048
# define LL_MAXOU 9223372036854775807ULL

# define IN_REDICT_ERROR  "syntax error near unexpected token `<'\n"
# define OUT_REDICT_ERROR "syntax error near unexpected token `>'\n"
# define HERE_DOC_ERROR   "syntax error near unexpected token `<<'\n"
# define OUT_APPEND_ERROR "syntax error near unexpected token `>>'\n"
# define NEWLINE_ERROR "syntax error near unexpected token `newline'\n"
# define PIPE_ERROR "syntax error near unexpected token `|'\n"
# define TRIPLE_IN_CHEVRON_ERROR "syntax error near unexpected token `<<<'\n"
# define TRIPLE_OUT_CHEVRON_ERROR "syntax error near unexpected token `>>>'\n"

typedef struct s_data	t_data;

typedef enum e_signals
{
	DEFAULT_SIG = 1,
	HEREDOC_SIG,
	CHILD_SIG,
	PARENT_SIG
}						t_signals;

typedef enum e_tokens
{
	SPACES,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	PIPE,
	ALPHANUMERIC,
	DOLLAR,
	INTERRO,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	CMD,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_SUR,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_RET,
}						t_tokens;

typedef struct s_env
{
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct t_here
{
	char				*delim;
	int					pipe[2];
}						t_here;

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
	struct s_list		*prev;
	t_data				*data;
	t_tokens			token;
	int					indice;
}						t_list;

typedef struct s_exec
{
	char				**path;
	pid_t				*pids;
	int					fd[2];
	int					prev;
	char				**cmds;
	char				*cmdpath;
	int					j;
}						t_exec;

typedef struct s_data
{
	t_list				*first;
	t_list				*last;
	int					exit_code;
	struct s_env		*env_list;
	char				**envi;
	char				***tb_cmd;
	t_exec				*exec;
	int					nb_cmd;
	int					nb_here;
	t_here				*here;
	int					n;
	int					here_status;
	int					w;
}						t_data;

/*BUILTIN*/

/* *** cd.c *** */

int						cd_to_many(char **cmd);
int						cd_home(char **cmd, char **env, t_data *data);
int						cd_minus(char **cmd, char **env, t_data *data);
int						cd_point_point(t_data *data);
int						cd(char **cmd, t_data *data);

/* *** cd2.c *** */

int						cd_home2(char **cmd, char **env, t_data *data);
int						cd_minus2(char **cmd, char **env, t_data *data);
int						cd_point_point2(t_data *data);
int						cd2(char **cmd, t_data *data);
void					modif_env(t_data *data, char *new_pwd);

/* *** echo.c *** */

void					parse_echo_option(char **echo, int *i, int *n);
void					echo(char **echo);

/* *** env_builtin.c *** */

int						contains_equal(char *s);
void					env_builtin(char **env);

/* *** exit_builtin.c *** */

long long				ft_atoull_exit(char *str, int e);
int						ft_is_sign(char c);
int						exit_error(char **cmd, t_data *data, int e);
int						exit_builtin(char **cmd, t_data *data, int e);

/* *** export_noargs.c *** */

void					sort_index(char **tab, int *index, int size);
void					print_export(char **tab, int *index, int size);
void					export_noargs(char **env);
void					export2(char **cmd, t_data *data);
void					ft_swap(int *a, int *b);

/* *** export.c *** */

int						parse_export(char *new_export_var);
int						add_to_env(char *cmd, t_env **envi);
int						update_env(char *cmd, t_env **envi);
int						export(char **cmd, t_data *data);
void					update_lst_env(char *cmd, t_env **env, char **var);

/* *** ft_printf_fd.c *** */

int						putchar_pf(char c, int fd);
int						putstr_pf(char *s, int fd);
int						utnbr_pf(int nb, int *count, int fd);
int						print_conversion(va_list *args, const char *s,
							int i, int fd);
int						ft_printf_fd(int fd, const char *s, ...);

/* *** pwd.c *** */

int						pwd(void);

/* *** signal.c *** */

void					antislash(int sig);
void					reactiv(int sig);
void					ctrlc(int sig);
void					ctrlc_2(int sig);
void					ctrlc_child(int sig);

/* *** unset_utils.c *** */

int						ft_lstsize_env(t_env *lst);
void					ft_lstdelone_env(t_env *lst, void (*del)(void *));
void					ft_lstclear_env(t_env **lst, void (*del)(void *));
t_env					*ft_lstlast_env(t_env *lst);
void					ft_lstadd_back_env(t_env **lst, t_env *newl);

/* *** unset.c *** */

t_env					*return_link_by_str(t_env *env, char *str);
t_env					*ft_lstnew_env(void *content);
int						pop_node(t_env **head, t_env *to_remove);
int						unset_end(t_data *data);
int						unset(char **cmd, t_data *data, int i, int j);

/* *** utils.c *** */

char					*ft_get_env(char *var_name, char **env);
char					*trim_path(char *path);
int						ft_strlen_tab(char **tab);
void					sub_cd(t_data *data, char *cmd);
int						is_builtin(char **cmds);

/* *** utils2.c *** */

t_env					*env_to_lst(char **env);
char					*get_env(char *var_name, char **env);
char					**copy_tab(char **src);
char					**lst_to_chartab(t_env *env);

/*EXTRA*/

/* *** free_data.c ***  */

void					free_list(t_list *lst);
void					free_list_env(t_env *env);
void					free_data_2_and_exit(t_data *data, int code);
void					free_data_2(t_data *data);
void					free_data_loop(t_data *data);

/* *** main_utils.c *** */

t_data					*starton(void);
void					exec_loop(t_data *data, char*line);
void					handle_signal(void);
t_data					*init_data(char **env);

/*PARSING*/

/* *** dollar_quote.c *** */

char					*replace_dollar_alpha(t_list *lst);
char					*replace_dollar_digit(t_list *lst);
char					*replace_dollar_return_code(t_list *lst);
int						var_env_len(char *str);
int						var_dollar_len(char *str);

/* *** dollar_quote2.c *** */

char					*get_path_var(t_env *env, char *str, int i);
char					*replace_alpha_null(t_list *lst, int i);
char					*replace_alpha_env(t_list *lst, char *str, int i);

/* *** dollar.c *** */

void					replace_dollar(t_data *data);
char					*replace_dollar_alpha2(t_list *lst);
char					*replace_dollar_digit2(t_list *lst);
char					*replace_dollar_return_code2(t_list *lst);
void					integration(t_list **lst);

/* *** dollar2.c *** */

char					*replace_alpha_null2(t_list *lst);
char					*replace_alpha_env2(t_list *lst, char *str);

/* *** dollar3.c *** */

void					replace_dollar_sub(t_list **lst, t_list *tmp);
void					replace_dollar_sub2(t_list **lst, t_list *tmp);

/* *** enum_utils.c *** */

void					set_token_type(t_list *tmp);
void					join_link(t_data *data);

/* *** enum.c *** */

t_tokens				get_token(char *str);
t_tokens				get_token2(char *str);
void					get_token3(t_list **list);
void					get_token4(t_list **list);
void					get_token5(t_list **list);

/* *** env.c *** */

t_env					*ft_envnew(char *content);
t_env					*ft_envadd_back(t_env **lst, t_env *new);
t_env					*creat_env_lst(char **content);
void					free_env(t_env *env);
char					**env2(t_env *env);

/* *** structure.c *** */

t_list					*ft_lstnew(t_data *data, char content, int i);
t_list					*ft_lstadd_back(t_list **lst, t_list *new);
void					creat_list(char *str, t_data *dbl_list);
char					*c_to_str(char c);
void					del_link(t_list *lst);

/* *** structure2_2.c *** */

void					free_tab2(char ***tab);
void					free_tab(char ***tab);
int						nb_cmd(t_list *lst);

/* *** structure2.c *** */

t_list					*ft_lstnew2(t_data *data, char content, int i);
void					creat_list2(char *str, t_data *dbl_list, t_list **first,
							t_list **last);
void					join_link2(t_list **first, t_list **last);
char					***tab_cmd(t_data *dbl_list);
int						sub_tab_cmd(t_list **tmp, char ****tab, int *i);

/* *** syntax_error_utils.c *** */

int						str_syntax_error_checking(t_data *data, t_list *tmp);

/* *** syntax_error.c *** */

int						syntax_error(t_data *data);
int						verif_spaces_chevron(t_list *tmp);
int						verif_chev_next_chev(t_list *tmp);
int						verif_pipe(t_list *tmp);
void					check_quotes_loop(t_data *data, char *line);

/* *** verif_quote.c *** */

int						verif_quote(char *line, t_data *data);
void					ft_negative(char *line);
void					ft_positive(t_data *data);
void					replace_quote(t_data *data);
void					replace_dollar_quote(t_list *lst);

/* *** verif_quote_utils.c *** */

t_list					*replace_single_quotes(t_list *tmp, int *i);
t_list					*replace_double_quotes(t_list *tmp, int *i);

/*PIPEX*/

/* *** builtin.c *** */

int						ft_verif_built(char **cmds, t_data *data);
void					ft_verif_built2(char **cmds, t_data *data);

/* *** free.c *** */

void					free_tab1(char **tab);
void					free_all_data(t_data *data, int code, int code2);
void					free_data(t_data *data);

/* *** here_doc_utils.c *** */

int						get_len_word(char *str);
void					get_word1(char **str);
int						get_word2(char *str, char **new, int *i, int *r);
void					get_word3(t_list **tmp, char *new);
char					*get_word(char *str, t_list **tmp);

/* *** here_doc.c *** */

void					here_doc_2(t_data *data);
t_here					*here_doc(t_data *data, char *str);
int						count_hd(t_list *list);
void					check_quotes(int *i, char *str);
void					ft_getdelims(char *str, t_here *here, t_data *data);

/* *** here_doc2.c *** */

void					child_hd(t_data *data, char *str);
char					*openfileshd(int index, t_here *here);

/* *** parsing.c *** */

char					*get_path_var1(char **env);
char					**get_paths_from_environment(char *path);
char					*access_check(char **env, char *cmd);
int						ft_strcmp(const char *s1, const char *s2);

/* *** pipex_utils.c *** */

void					close_fd(int *fd);
void					close_pipes(t_data *data);
void					child_process_2(t_data *data, char ***cmds, int i,
							t_list **tmp);
int						init(t_data *data);

/* *** pipex.c *** */

void					wait_all_child(t_data *data, int i);
void					close_all_pipes(t_data *data);
void					handle_parent_process(t_data *data, int i);
void					loop_cmd(t_data *data);
void					exec_cmd(t_data *data);

/* *** redirect_fd.c *** */

int						getpipe(t_here *here, t_data *data, char *file);
void					redirect(t_data *data);
int						open_file2(int fd, t_list *tmp, t_data *data);
int						redirect2(t_data *data, t_list *tmp1);

#endif
