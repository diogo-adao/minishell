/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:04 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/09 20:01:22 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_pid(t_exec_ctx *ctx)
{
	int	exit_code;

	if (ctx->cmd->pid == 0)
	{
		exit_code = ctx->cmd->exit;
		free_all(ctx->list, ctx->line, ctx->head, 1);
		free_arr(*(ctx->env));
		free(*(ctx->_pipe));
		exit(exit_code);
	}
	if (ctx->cmd->args && ctx->cmd->pid == 1 && !ft_strncmp(ctx->cmd->args[0], "exit", 4)
		&& ft_strlen(ctx->cmd->args[0]) == 4 && !ctx->cmd->prev && !ctx->cmd->next)
	{
		if (ctx->cmd->args[1] && is_numeric(ctx->cmd->args[1]))
		{
			if (ctx->cmd->args[2])
				return ;
		}
		printf("exit\n");
		exit_code = ctx->cmd->exit;
		free_all(ctx->list, ctx->line, ctx->cmd, 1);
		free_arr(*(ctx->env));
		free(*(ctx->_pipe));
		exit(exit_code);
	}
}

void	wait_pid(t_cmd *cmd)
{
	int	status;

	status = 0;
	while (cmd)
	{
		if (cmd->next)
			waitpid(cmd->pid, NULL, 0);
		else
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (!exit_status)
					exit_status = cmd->exit;
				return ;
			}
		}
		cmd = cmd->next;
	}
}

void exec_cmd(t_exec_ctx *ctx)
{
    if ((!ft_strncmp(ctx->cmd->args[0], "echo", 4)
            && ft_strlen(ctx->cmd->args[0]) == 4))
        builtin_echo(ctx->cmd);
    else if ((!ft_strncmp(ctx->cmd->args[0], "env", 3)
            && ft_strlen(ctx->cmd->args[0]) == 3))
        builtin_env(*ctx->env);
    else if ((!ft_strncmp(ctx->cmd->args[0], "unset", 5)
            && ft_strlen(ctx->cmd->args[0]) == 5))
        builtin_unset(ctx->cmd, *ctx->env);
    else if ((!ft_strncmp(ctx->cmd->args[0], "export", 6)
            && ft_strlen(ctx->cmd->args[0]) == 6))
        builtin_export(ctx->cmd, ctx->env);
    else if ((!ft_strncmp(ctx->cmd->args[0], "cd", 2)
            && ft_strlen(ctx->cmd->args[0]) == 2))
        builtin_cd(ctx->cmd, ctx->env);
    else if ((!ft_strncmp(ctx->cmd->args[0], "pwd", 3)
            && ft_strlen(ctx->cmd->args[0]) == 3))
        builtin_pwd();
    else if ((!ft_strncmp(ctx->cmd->args[0], "exit", 4)
            && ft_strlen(ctx->cmd->args[0]) == 4))
        builtin_exit(ctx->cmd);
    else
        not_builtin(ctx);
    check_pid(ctx);
}

void set_cmd(t_exec_ctx *ctx, int i)
{
    int fd[2];

	fd[0] = dup(STDIN_FILENO);
    fd[1] = dup(STDOUT_FILENO);
	if (ctx->cmd->pid == 0)
		pipe_fd(ctx->head, ctx->cmd, ctx->_pipe, i);
    if (exec_redir(ctx->cmd))
    {
        if (ctx->cmd->args)
        	exec_cmd(ctx);
    }
	else
		check_pid(ctx);
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}

void	start_execution(t_cmd *cmd, char ***env, t_token *list, char *line)
{
	int			(*_pipe)[2];
	t_exec_ctx	ctx;

	ctx.head = cmd;
	ctx.env = env;
	ctx._pipe = &_pipe;
	ctx.list = list;
	ctx.line = line;
	signal(SIGQUIT, signal_handler);
	if (is_heredoc(cmd))
		return ;
	create_pipes(cmd, &_pipe);
	start_execution_loop(&ctx, cmd);
	close_pipe(ctx.head, &_pipe);
	wait_pid(ctx.head);
	free(*_pipe);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
