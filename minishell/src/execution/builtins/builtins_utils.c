/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:21:04 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/23 18:28:57 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_cd_error(char *dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, dir, ft_strlen(dir));
	if (access(dir, F_OK) == 0)
		write(2, ": Not a directory\n", 18);
	else
		write(2, ": No such file or directory\n", 28);
}

void	print_getcwd_error(t_cmd *cmd)
{
	write(2, "minishell: cd: error retrieving current directory: getcwd: ", 60);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	cmd->exit = 1;
}

void	handle_pwd_update(char ***env)
{
	char	path[1024];
	char	*new_entry;

	if (getcwd(path, sizeof(path)))
	{
		new_entry = ft_strjoin("PWD=", path);
		if (!new_entry)
			return ;
		if (update_env(env, "PWD", new_entry, 3))
			return (free(new_entry));
		append_to_env(env, new_entry);
		free(new_entry);
	}
}

void	handle_oldpwd_update(char ***env)
{
	char	*old;
	char	*new_entry;

	old = ft_get_env(*env, "OLDPWD");
	if (old)
	{
		new_entry = ft_strjoin("OLDPWD=", old);
		if (!new_entry)
			return ;
		if (update_env(env, "OLDPWD", new_entry, 6))
			return (free(new_entry));
		append_to_env(env, new_entry);
		free(new_entry);
	}
}

void	export_non_append(char ***env, char *arg, char *key)
{
	char	*new_entry;

	new_entry = ft_strdup(arg);
	if (!new_entry)
		return (free(key));
	if (update_env(env, key, new_entry, ft_strlen(key)))
		return (free(key), free(new_entry));
	append_to_env(env, new_entry);
	free(new_entry);
	free(key);
}
