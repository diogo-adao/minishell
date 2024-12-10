/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:53:00 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/10 16:27:01 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libraries/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
	char *type;
    char **tokens;   // Array of tokens (parsed input)
    int token_count; // Number of tokens
	int option;
} t_data;

#endif
