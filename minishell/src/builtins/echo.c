/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:11:35 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/13 18:56:58 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * builtin_echo() starts by checking if -n option is present.
 * it uses is_option_n() that starts by checking if the first character is '-'
 * if true: it iterates the string while it finds 'n'
 * if any other char is found the option is invalid so it gets treated as a
 * normal string to get printed.
 * In the end it iterates the rest of the command and prints each argument.
 */

bool	is_option_n(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(t_cmd *cmd)
{
	bool	newline;
	int		i;

	newline = true;
	i = 1;
	while (cmd->args[i] && is_option_n(cmd->args[i]))
	{
		newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

// Main for testing
/* int main()
{
	char *args[] = {"echo", "$PATH", NULL};
	t_cmd cmd = {args, 0, 0, NULL};

	builtin_echo(&cmd);
	return (0);
} */
