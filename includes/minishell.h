/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:53:00 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/17 17:24:44 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libraries/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

typedef struct	s_token
{
	char				*value;
	int						type;
	struct s_token	*next;
}	t_token;

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

void	builtins(char	*l);
int	validqn(char *line);
char	*ft_copy(char *line);
char	*simplequotes(char *line);
char	*removequote(char *line, int t, int i);
char	*dolarparsing(char *line);
#endif
