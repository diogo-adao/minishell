/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:35 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/17 15:29:22 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	check_overflow(const char *str, int i, int sign)
{
	unsigned long long	num;
	unsigned long long	limit;

	num = 0;
	if (sign == -1)
		limit = (unsigned long long)LLONG_MAX + 1;
	else
		limit = (unsigned long long)LLONG_MAX;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		num = num * 10 + (str[i] - '0');
		if (num > limit)
			return (false);
		i++;
	}
	return (true);
}

bool	is_numeric(const char *str)
{
	int	i;
	int	sign;

	if (!str || !str[0])
		return (false);
	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (false);
	return (check_overflow(str, i, sign));
}

void	builtin_exit(t_cmd *cmd)
{
	if (!cmd->prev && !cmd->next && cmd->pid == 1)
		printf("exit\n");
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, cmd->args[1], ft_strlen(cmd->args[1]));
			write(2, ": numeric argument required\n", 28);
			cmd->exit = 2;
			return ;
		}
		if (cmd->args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			cmd->exit = 1;
			return ;
		}
		cmd->exit = ft_atoi(cmd->args[1]) % 256;
		if (cmd->exit < 0)
			cmd->exit += 256;
	}
	else
		cmd->exit = get_exit_status();
}
