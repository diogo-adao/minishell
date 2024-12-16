/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:31 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/16 16:49:15 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * builtin_env() simply uses the variable 'envp' that holds all the environment
 * variables and iterates through the list while printing each one.
 */

int builtin_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

// Main for testin
/* int main(int argc, char **argv, char **envp)
{
	builtin_env(envp);
	return (0);
} */
