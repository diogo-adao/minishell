/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:35 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/13 19:39:33 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

int	builtin_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", cmd->args[1]);
			cmd->exit = 2;
			exit(cmd->exit);
		}
		if (cmd->args[2])
		{
			printf("bash: exit: too many arguments\n");
			return (1);
		}
		cmd->exit = ft_atoi(cmd->args[1]) % 256;
		if (cmd->exit < 0)
			cmd->exit += 256;
		exit(cmd->exit);
	}
	exit(0);
}

// Main for testing
/* int main()
{
	char *args[] = {"exit", "10", "20", NULL};
	t_cmd cmd = {args, 0, 0, NULL};
	builtin_exit(&cmd);
	return (0);
} */
