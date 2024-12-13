/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:53:00 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/13 19:39:31 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libraries/libft.h"

// Token types
typedef enum
{
	STRING,
	REDIR,
	PIPE,
}  e_token_type;

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
	int redir; // Redirections flag
	int exit;
	struct s_cmd *next; // Check for pipe (next command)
}	t_cmd;


/* typedef struct s_nodetest
{
	int	type;
}	t_nodetest;

typedef struct s_cmdtest
{
	int		type;
	t_token	*args;
	t_token	*redirs;
}	t_cmdtest;

typedef struct s_pipetest
{
	int			type;
	t_nodetest	*left;
	t_nodetest	*right;
}	t_pipetest; */

#endif
