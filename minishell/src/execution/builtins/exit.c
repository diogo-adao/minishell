/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:35 by diolivei          #+#    #+#             */
/*   Updated: 2025/03/18 17:02:34 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

void	builtin_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			cmd->exit = 2;
			return;
		}
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			cmd->exit = 1;
			return;
		}
		cmd->exit = ft_atoi(cmd->args[1]) % 256;
		if (cmd->exit < 0)
			cmd->exit += 256;
	}
	else
		cmd->exit = 0;
}
