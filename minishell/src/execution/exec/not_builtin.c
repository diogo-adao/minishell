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

void exec_path(t_cmd *cmd, char *cmd_path, char **env)
{
	struct stat	buf;

	execve(cmd_path, cmd->args, env);
	//free(cmd_path);
	if (stat(cmd->args[0], &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
}

void	not_builtin(t_cmd *cmd, char **env)
{
	char *cmd_path;

	if (!cmd->args[0][0])
		return ;
	cmd_path = search_path(cmd, env);
	if (!cmd_path)
	{
		if (cmd->args[0][0] == '.' || ft_strchr(cmd->args[0], '/'))
			ft_putstr_fd("minishell: No such file or directory\n", 2);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		cmd->exit = 127;
		return ;
	}
	exec_path(cmd, cmd_path, env);
	free(cmd_path);
}
