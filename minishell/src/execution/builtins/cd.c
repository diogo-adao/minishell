/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:46 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/23 18:24:26 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_existing_pwd(char ***env, char *new_pwd, char **old_pwd)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], "PWD=", 4))
		{
			*old_pwd = ft_strjoin("OLD", (*env)[i]);
			if (!(*old_pwd))
				return (0);
			free((*env)[i]);
			(*env)[i] = new_pwd;
			return (1);
		}
		i++;
	}
	return (0);
}

void	update_pwd(char ***env, char *path)
{
	char	*new_pwd;
	char	*old_pwd;
	int		pwd_found;

	new_pwd = ft_strjoin("PWD=", path);
	if (!new_pwd)
		return ;
	old_pwd = NULL;
	*env = remove_from_env(*env, "OLDPWD");
	pwd_found = update_existing_pwd(env, new_pwd, &old_pwd);
	if (pwd_found && old_pwd)
		append_to_env(env, old_pwd);
	else
		free(new_pwd);
	free(old_pwd);
}

void	change_dir(t_cmd *cmd, char ***env, char *dir)
{
	char	path[1024];
	char	*cwd;

	if (chdir(dir) == -1)
	{
		print_cd_error(dir);
		cmd->exit = 1;
		return ;
	}
	cwd = getcwd(path, sizeof(path));
	if (!cwd)
		print_getcwd_error(cmd);
	else
	{
		update_pwd(env, cwd);
		cmd->exit = 0;
	}
}

void	builtin_cd(t_cmd *cmd, char ***env)
{
	char	*path;

	if (!cmd->args[1])
	{
		path = ft_get_env(*env, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			cmd->exit = 1;
		}
		else
		{
			change_dir(cmd, env, path);
			free(path);
		}
	}
	else if (cmd->args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		cmd->exit = 1;
	}
	else
		change_dir(cmd, env, cmd->args[1]);
}
