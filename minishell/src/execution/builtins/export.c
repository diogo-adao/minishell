/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:38 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/17 15:31:06 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	no_args(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!((str[0] >= 'a' && str[0] <= 'z') || \
		(str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (0);
	while (str[++i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || \
			(str[i] >= 'A' && str[i] <= 'Z') || \
			(str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (0);
	}
	return (1);
}

int	update_existing_env(char ***env, char *key, char *new_entry, size_t key_len)
{
	int	i;

	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], key, key_len)
			&& (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_entry;
			return (1);
		}
	}
	return (0);
}

void	export_env(char ***env, char *arg)
{
	char	*key;
	char	*pos;
	char	*new_entry;

	pos = ft_strchr(arg, '=');
	if (!pos)
		return ;
	key = ft_substr(arg, 0, pos - arg);
	new_entry = ft_strdup(arg);
	if (!new_entry)
		return (free(key), (void)0);
	if (update_existing_env(env, key, new_entry, pos - arg))
		return (free(key), (void)0);
	append_to_env(env, new_entry);
	free(new_entry);
	free(key);
}

void	builtin_export(t_cmd *cmd, char ***env)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
		no_args(*env);
	else
	{
		while (cmd->args[++i])
		{
			if (!is_valid(cmd->args[i]))
			{
				write(2, "minishell: export: ", 19);
				write(2, cmd->args[i], ft_strlen(cmd->args[i]));
				write(2, ": not a valid identifier\n", 25);
				cmd->exit = 1;
				break ;
			}
			if (ft_strchr(cmd->args[i], '='))
				export_env(env, cmd->args[i]);
		}
	}
}
