/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:42:29 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/21 19:36:41 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_child_exit(t_exec_ctx *ctx)
{
	int	exit_code;

	exit_code = ctx->cmd->exit;
	free_all(ctx->list, ctx->line, ctx->head, 1);
	free_arr(*(ctx->env));
	free(*(ctx->_pipe));
	exit(exit_code);
}

void	handle_builtin_exit(t_exec_ctx *ctx)
{
	int	exit_code;

	if (ctx->cmd->args[1] && is_numeric(ctx->cmd->args[1]))
	{
		if (ctx->cmd->args[2])
			return ;
	}
	exit_code = ctx->cmd->exit;
	free_all(ctx->list, ctx->line, ctx->cmd, 1);
	free_arr(*(ctx->env));
	free(*(ctx->_pipe));
	exit(exit_code);
}

void	signal_handler(int sig)
{
	pid_t	pid;
	int		stat;

	pid = waitpid(-1, &stat, WNOHANG);
	if (sig == SIGINT)
	{
		if (pid == 0)
			printf("\n");
		else
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (pid == 0)
			printf("Quit (core dumped)\n");
		g_exit_status = 131;
	}
}

int	is_builtin(char *arg)
{
	if ((!ft_strncmp(arg, "echo", 4) && ft_strlen(arg) == 4)
		|| (!ft_strncmp(arg, "env", 3) && ft_strlen(arg) == 3)
		|| (!ft_strncmp(arg, "unset", 5) && ft_strlen(arg) == 5)
		|| (!ft_strncmp(arg, "export", 6) && ft_strlen(arg) == 6)
		|| (!ft_strncmp(arg, "cd", 2) && ft_strlen(arg) == 2)
		|| (!ft_strncmp(arg, "pwd", 3) && ft_strlen(arg) == 3)
		|| (!ft_strncmp(arg, "exit", 4) && ft_strlen(arg) == 4))
		return (1);
	return (0);
}

void	start_execution_loop(t_exec_ctx *ctx, t_cmd *cmd)
{
	int	i;

	signal(SIGINT, SIG_IGN);
	i = 0;
	while (cmd)
	{
		ctx->cmd = cmd;
		if (cmd->args && (!is_builtin(cmd->args[0]) || cmd->next || cmd->prev))
		{
			cmd->pid = fork();
			if (ft_strncmp(cmd->args[0], "./minishell", 11) == 0)
				signal(SIGQUIT, SIG_IGN);
		}
		else
			cmd->pid = 1;
		if (cmd->pid == 0 || cmd->pid == 1)
		{
			if (cmd->pid == 0)
				signal(SIGINT, signal_handler);
			set_cmd(ctx, i);
		}
		cmd = cmd->next;
		i++;
	}
}
