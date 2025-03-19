/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:46 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/16 16:06:50 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd(char ***env, char *path)
{
	int		i;
	char	*new_pwd;
	char	*old_pwd;

	i = 0;
	new_pwd = ft_strjoin("PWD=", path);
	if (!new_pwd)
		return ;
	old_pwd = NULL;
	*env = remove_from_env(*env, "OLDPWD");
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], "PWD", 3) && (*env)[i][3] == '=')
		{
			old_pwd = ft_strjoin("OLD", (*env)[i]);
			free((*env)[i]);
			(*env)[i] = old_pwd;
		}
		i++;
	}
	append_to_env(env, new_pwd);
    free(new_pwd);
}

void change_dir(t_cmd *cmd, char ***env, char *dir)
{
    char path[1024];

    if (chdir(dir) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(dir, 2);
        if (access(dir, F_OK) == 0)
            ft_putstr_fd(": Not a directory\n", 2);
        else
            ft_putstr_fd(": No such file or directory\n", 2);
        cmd->exit = 1;
    }
    else
    {
        getcwd(path, sizeof(path));
		if(path[0] != '\0')
			update_pwd(env, path);
    }
}

void builtin_cd(t_cmd *cmd, char ***env)
{
    char *path;

    if (!cmd->args[1])
    {
        path = ft_get_env(*env, "HOME");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
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
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        cmd->exit = 1;
    }
    else
        change_dir(cmd, env, cmd->args[1]);
}
