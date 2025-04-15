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

void exec_path(t_cmd *head, t_cmd *cmd, char *cmd_path, char **env, t_token *list, char *line, int (**_pipe)[2])
{
	struct stat	buf;

	execve(cmd_path, cmd->args, env);
	if (stat(cmd->args[0], &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": Is a directory\n", 18);
		free_all(list, line, head, 1);
		free_arr(env);
		free(*_pipe);
		exit(126);
	}
}

void	not_builtin(t_cmd *head, t_cmd *cmd, char **env, t_token *list, char *line, int (**_pipe)[2])
{
	char *cmd_path;

	if (!cmd->args[0][0])
		return ;
	cmd_path = search_path(cmd, env);
	if (!cmd_path)
	{
		if (cmd->args[0][0] == '.' || ft_strchr(cmd->args[0], '/'))
			write(2, "minishell: No such file or directory\n", 37);
		else
		{
			write(2, "minishell: ", 11);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": command not found\n", 21);
		}
		cmd->exit = 127;
		return ;
	}
	exec_path(head, cmd, cmd_path, env, list, line, _pipe);
	free(cmd_path);
}
