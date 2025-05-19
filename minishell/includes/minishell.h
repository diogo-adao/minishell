/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:53:00 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/19 16:32:54 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * verificar os signals no pc da escola
 * g_exit_status só pode receber signals
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft.h"

// Token types
typedef enum token_type
{
	STRING,
	REDIR,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}	t_token_type;

// Redirections
typedef struct s_redir
{
	int			flag; // Type of redirection
	char		*file; // File name
}	t_redir;

// Parser Struct
typedef struct s_token
{
	char			*value; // Token
	int				type; // Token Type
	struct s_token	*next; // Next Token
}	t_token;

// Executor struct
typedef struct s_cmd
{
	char			**args; // Command and its arguments
	int				exit; // Exit status
	int				pid; // Parent and child processes
	t_redir			**redir; // Redirections struct
	struct s_cmd	*next; // Check for pipe (next command)
	struct s_cmd	*prev; // previus command
}	t_cmd;

typedef struct aux
{
	t_token	*list;
	t_token	*new_node;
	int		i;
	int		start;
}	t_aux;

// Struct for norm
typedef struct s_exec_ctx
{
	t_cmd		*head;
	t_cmd		*cmd;
	char		***env;
	int			(**_pipe)[2];
	t_token		*list;
	char		*line;
}	t_exec_ctx;

// Global variable for exit status
extern int	g_exit_status;

// Parser functions
void	builtins(char *line, char ***env);
int		validqn(char *line);
char	*ft_copy(char *line);
char	*literalparsing(char *new);
char	*removequote(char *line, int t, int i);
char	*dolarparsing(char *line, char **env);
char	*combine(char *line, char *expenv, int t, int i);
char	*dolar(char *line, char **env);
char	**ownenvp(char **envp);
char	*ft_getenv(char *exp, char **env);
void	literallist(t_token *list);
void	free_listt(t_token *list);
t_token	*creatlist(char *line);
void	free_all(t_token *list, char *line, t_cmd *cmd, int i);
void	free_env(char **env);
int		checker_list(t_token *list);
int		cheker_comands(t_token *list);
t_cmd	*execute_p(t_token *list);
void	print_tokens(t_token *list); //funcao simples para imprimir
void	print_exec(t_cmd *list); // teste
char	*getexp(char *line, int t, int i, char **env);
char	**zero_envp(void);
char	*allt(char *p1, char *p2, char *p3);
void	skip_wordh(int *i, char *line);

//execute_p
t_redir	**redir_fill(t_redir **redir, t_token *list, int i);
char	**arg_fill(char **args, t_token *list, int i);
int		string_count(t_token *list);
int		redir_count(t_token *list);
int		get_type(t_token *list);

//expansao
int		explen(char	*line, int i);
int		endofexp(char letter);
char	*add_fandl(char *line, char a);
char	*dolarparsing(char *line, char **env);
void	handle_double_quotes(int *i, char **line, char **temp, char **env);
void	handle_dollar_inside_quotes(int *i, char **l, char **temp, char **env);
void	handle_single_quotes(int *i, char **line);
void	handle_dollar_sign(int *i, char **line, char **temp, char **env);
void	handle_exit_status(int *i, char **line, char **temp);

// Executor functions
char	*ft_get_env(char **env, char *key);
void	append_to_env(char ***env, char *new_var);
char	**remove_from_env(char **env, char *to_remove);
void	free_arr(char **arr);
void	signal_handler(int sig);
int		exec_redir(t_cmd *cmd);
void	not_builtin(t_exec_ctx *ctx);
void	close_pipe(t_cmd *cmd, int (**_pipe)[2]);
int		is_heredoc(t_cmd *cmd, char ***env);
void	create_pipes(t_cmd *cmd, int (**_pipe)[2]);
int		is_builtin(char *arg);
void	start_execution(t_cmd *cmd, char ***env, t_token *list, char *line);
void	start_execution_loop(t_exec_ctx *ctx, t_cmd *cmd);
void	set_cmd(t_exec_ctx *ctx, int i);
void	handle_child_exit(t_exec_ctx *ctx);
void	handle_builtin_exit(t_exec_ctx *ctx);
void	pipe_fd(t_cmd *head, t_cmd *cmd, int (**_pipe)[2], int i);
void	builtin_pwd(void);
void	builtin_unset(t_cmd *cmd, char **env);
void	builtin_export(t_cmd *cmd, char ***env);
void	builtin_exit(t_cmd *cmd);
void	builtin_env(char **envp);
void	builtin_echo(t_cmd *cmd);
void	builtin_cd(t_cmd *cmd, char ***env);
bool	is_numeric(const char *str);
void	sort_env(char **env);
char	**copy_env(char **env);
void	print_export(char *str);
int		update_env(char ***env, char *key, char *new_entry, size_t key_len);
char	*find_env_value(char **env, char *key);
void	handle_append(char ***env, char *key, char *pos);

#endif
