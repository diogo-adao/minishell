/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:16 by diolivei          #+#    #+#             */
/*   Updated: 2025/02/04 19:41:34 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *build_path(t_cmd *cmd, char **arr)
{
	int i;
	char *final_path;
	char *temp;

	i = -1;
	while (arr && arr[++i])
	{
		temp = ft_strjoin(arr[i], "/");
		final_path = ft_strjoin(temp, cmd->args[0]);
		free(temp);
		if (access(final_path, F_OK) == 0)
		{
			free_arr(arr);
			return (final_path);
		}
		free(final_path);
	}
	if (arr)
		free_arr(arr);
	return (NULL);
}

char *search_path(t_cmd *cmd, char **env)
{
	char *path;
	char **arr;
	char *final_path;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK) == 0)
			return (cmd->args[0]);
		return (NULL);
	}
	path = ft_get_env(env, "PATH");
	if (!path || !(arr = ft_split(path, ':')))
	{
		free(path);
		return (NULL);
	}
	free(path);
	final_path = build_path(cmd, arr);
	return (final_path);
}

void exec_path(t_exec_ctx *ctx, char *cmd_path)
{
	struct stat	buf;

	execve(cmd_path, ctx->cmd->args, *ctx->env);
	if (stat(ctx->cmd->args[0], &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, ctx->cmd->args[0], ft_strlen(ctx->cmd->args[0]));
		write(2, ": Is a directory\n", 18);
		free_all(ctx->list, ctx->line, ctx->head, 1);
		free_arr(*(ctx->env));
		free(*(ctx->_pipe));
		exit(126);
	}
}

void	not_builtin(t_exec_ctx *ctx)
{
	char *cmd_path;

	if (!ctx->cmd->args[0][0])
		return ;
	cmd_path = search_path(ctx->cmd, *ctx->env);
	if (!cmd_path)
	{
		if (ctx->cmd->args[0][0] == '.' || ft_strchr(ctx->cmd->args[0], '/'))
			write(2, "minishell: No such file or directory\n", 37);
		else
		{
			write(2, "minishell: ", 11);
			write(2, ctx->cmd->args[0], ft_strlen(ctx->cmd->args[0]));
			write(2, ": command not found\n", 21);
		}
		ctx->cmd->exit = 127;
		return ;
	}
	exec_path(ctx, cmd_path);
	free(cmd_path);
}
