/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:11:35 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/12 19:09:24 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * builtin_echo() starts by checking if -n option is present.
 * it uses is_option_n() that starts by checking if the first character is '-'
 * if true: it iterates the string while it finds 'n'
 * if any other char is found the option is invalid so it gets treated as a
 * normal string to get printed.
 * In the end it iterates the rest of the list and prints each token value.
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

int	builtin_echo(t_token *tokens)
{
	bool	newline;
	t_token	*current;

	newline = true;
	current = tokens->next;
	while (current && is_option_n(current->value))
	{
		newline = false;
		current = current->next;
	}
	while (current)
	{
		printf("%s", current->value);
		if (current->next)
			printf(" ");
		current = current->next;
	}
	if (newline)
		printf("\n");
	return (0);
}

// Main for testing
/* int main()
{
	t_token arg3 = {"Hello", 0, NULL};
	t_token arg2 = {"-nf", 0, &arg3};
	t_token arg1 = {"-n", 0, &arg2};
	t_token echo_cmd = {"echo", 0, &arg1};

	builtin_echo(&echo_cmd);
	return (0);
} */
