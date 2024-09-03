/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:22:53 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/03 19:57:08 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <libft.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>
#include <types.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <termios.h>
#include <dirent.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_exit_stts;

/* FUNCTIONS */
t_cmd		*filter_empty_cmd(t_cmd *cmd);
void		join_tokens(t_tokenizer *token);
char		*sort_wildcard(char *wildcard);
char		*ft_wildcard(char *dirname);
void		throw_error(void);
void		close_all(void);
char		*remove_squotes(t_tokenizer *tmp, int *i);
char		*remove_dquotes(t_tokenizer *tmp, int *i);
void		join_tokens(t_tokenizer *token);
int			word_char(char c);
void		split_var(char *arg, char **id, char **value, int flag);
int			isvalid(char *arg, int *join_flag);
int			join_string(char c, char next_c, int is_last, int *flag);
int			ft_strnchr(const char *s, int c);
t_tokenizer	*make_node(char *input, int *j, t_lexer *type, t_stat *stat);
t_tokenizer	*token_word(char *input, t_lexer *type, int *i);
t_tokenizer	*sub_redirection(char *input, t_lexer *type, \
	int *i, t_stat *stat);
t_tokenizer	*token_special_char(char *input, t_lexer *type, int *i);
int			check_dquotes(t_stat **stat, char *input, int *i, int *j);
int			check_squotes(t_stat **stat, char *input, int *i, int *j);
void		process_dollar_question(char *token, int *i, char **join_it, \
				t_minishell *mini);
int			process(t_minishell *mini, t_cmd *cmds, int input, int output);
int			check_word_input(char c);
void		print_state(t_stat stat);
int			execute_builtin(t_minishell *mini, t_cmd *cmd);
int			red_process(t_minishell *mini, t_cmd *cmds, int input, int output);
int			is_builtins(t_cmd *cmds);
int			execute_single_commande(t_minishell *mini, t_cmd *cmd);
char		**env_to_array(t_env *env_list);
int			multi_process(t_minishell *mini, t_cmd *cmds);
char		*env_join(char const *s1, char const *s2);
int			single_process(t_minishell *mini, t_cmd *cmds);
int			node_len(t_cmd *cmds);
int			my_execve(t_minishell *mini, t_cmd *cmds);
char		*find_cmd(t_minishell *mini, char *cmd);
int			execution(t_minishell *mini, t_cmd *cmds);
void		del_one_env(t_env *lst, void (*del)(void *));
void		handle_sigint(int sig);
t_env		*new_env(char *key, char *value);
void		append_env(t_env **env, t_env *node);
char		*get_values(t_env **env, char *key);
int			set_env(t_env **env, char *key, char *value);
char		*get_value(t_minishell **mini, char *key);
int			env(t_env *env);
int			pwd(t_cmd *cmd);
int			export(t_cmd *cmd, t_env **env);
int			ft_exit(t_cmd *cmd, t_minishell *mini);
int			echo(t_cmd *cmd);
int			cd(t_cmd *cmd, t_env *env);
int			unset(t_cmd *token, t_env **env);
void		send_to_execution(t_tokenizer *token, t_cmd **cmd);
void		count_len(t_tokenizer *lst, int *commands_len, \
				int *redirection_len);
void		clear_cmd(t_cmd **cmd, void (*del)(void *));
void		del_one_cmd(t_cmd *cmds, void (*del)(void *));
t_cmd		*new_cmd(int cmd, int red, t_stat *stat);
void		append_to_exec(t_cmd **cmds, t_cmd *cmd);
int			between_pipe(t_tokenizer *lst);
int			ft_strcmp(char *s1, char *s2);
int			here_doc(t_tokenizer *delimiter, t_minishell *mini);
char		*expansion(char *token, t_minishell *mini);
int			store_env(char **envr, t_env **env);
t_tokenizer	*check_signle_quotes(char *input, int *i, t_lexer *type, \
				t_stat *stat);
t_tokenizer	*check_double_quotes(char *input, int *i, t_lexer *type, \
				t_stat *stat);
t_tokenizer	*make_node(char *input, int *j, t_lexer *type, t_stat *stat);
t_tokenizer	*new_token(void *content, t_lexer *type, \
	t_stat *stat, bool joinable);
void		print_token(t_tokenizer *token);
void		print_state(t_stat stat);
void		print_type(t_lexer lexer);
void		del_one_token(t_tokenizer *lst, void (*del)(void *));
void		clear_token(t_tokenizer **lst, void (*del)(void *));
int			lexer_first(t_tokenizer **token, char *input);
void		parse_input(t_minishell *mini, t_cmd **cmds);
void		append_token(t_tokenizer **tokens, t_tokenizer *token);
int			ft_isspace(char c);
int			is_special(int c);

/* SIGNALS */
void		handle_sigint(int sig);
void		set_sigs(void);
int			getexstatus(int stts);
void		reset_sigs(void);
