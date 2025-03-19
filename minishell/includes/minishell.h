/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:53:00 by diolivei          #+#    #+#             */
/*   Updated: 2025/03/18 18:08:47 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ***************ERROS AINDA POR RESOLVER***************
 * É preciso uma função para substituir $? pela global variable
 * Algo está errado com o parsing do dollar sign impedindo o uso correto do export
 * Tem leaks
 */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libraries/libft.h"

// Token types
typedef enum
{
	STRING,
	REDIR,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}  e_token_type;

// Redirections
typedef struct s_redir
{
	int			flag; // Type of redirection
	char		*file; // File name
}	t_redir;

// Parser Struct
typedef struct	s_token
{
	char			*value; // Token
	int				type; // Token Type
	struct s_token	*next; // Next Token
}	t_token;

// Executor struct
typedef struct s_cmd
{
	char **args; // Command and its arguments
	int exit; // Exit status
	int pid; // Parent and child processes
	t_redir **redir; // Redirections struct
	struct s_cmd *next; // Check for pipe (next command)
	struct s_cmd *prev; // previus command
}	t_cmd;

// Global variable for exit status
extern int exit_status;

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
char 	*ft_getenv(char *exp, char **env);
void 	literallist(t_token *list);
void	free_listt(t_token *list);
t_token *creatlist(char *line);
void	free_all(t_token *list, char *line, t_cmd *cmd, int i);
void	free_env(char **env);
int		checker_list(t_token *list);
int		cheker_comands(t_token *list);
t_cmd	*execute_p(t_token *list);
void	print_tokens(t_token *list); //funcao simples para imprimir
void print_exec(t_cmd *list); // teste

// Executor functions
char	*ft_get_env(char **env, char *key);
void	append_to_env(char ***env, char *new_var);
char	**remove_from_env(char **env, char *to_remove);
void	free_arr(char **arr);
void	signal_handler(int sig);
int		exec_redir(t_cmd *cmd);
void	not_builtin(t_cmd *cmd, char **env);
void	close_pipe(t_cmd *cmd, int (**_pipe)[2]);
int		is_heredoc(t_cmd *cmd);
void	create_pipes(t_cmd *cmd, int (**_pipe)[2]);
int		is_builtin(char *arg);
void    start_execution(t_cmd *cmd, char ***env);
void	free_cmd(t_cmd *cmd);
void	pipe_fd(t_cmd *head, t_cmd *cmd, int (**_pipe)[2], int i);
void	builtin_pwd();
void	builtin_unset(t_cmd *cmd, char **env);
void    builtin_export(t_cmd *cmd, char ***env);
void	builtin_exit(t_cmd *cmd);
void 	builtin_env(char **envp);
void	builtin_echo(t_cmd *cmd);
void	builtin_cd(t_cmd *cmd, char ***env);

#endif
