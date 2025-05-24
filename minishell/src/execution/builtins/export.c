/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:38 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/24 04:32:06 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	no_args(char **env)
{
	int		i;
	char	**sorted;

	sorted = copy_env(env);
	if (!sorted)
		return ;
	sort_env(sorted);
	i = 0;
	while (sorted[i])
	{
		print_export(sorted[i]);
		free(sorted[i]);
		i++;
	}
	free(sorted);
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!((str[0] >= 'a' && str[0] <= 'z') || \
		(str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (0);
	while (str[++i] && !(str[i] == '=' || (str[i] == '+' && str[i + 1] == '=')))
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || \
			(str[i] >= 'A' && str[i] <= 'Z') || \
			(str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (0);
	}
	return (1);
}

int	find_env_key(char **env, const char *key)
{
	size_t key_len = 0;
	while (key[key_len] && key[key_len] != '=' && key[key_len] != '+')
		key_len++;
	for (int i = 0; env[i]; i++)
	{
		if (!strncmp(env[i], key, key_len) && (env[i][key_len] == '=' || env[i][key_len] == '\0'))
			return i;
	}
	return -1;
}

char *str_join_and_free(char *s1, const char *s2)
{
	size_t len1 = s1 ? strlen(s1) : 0;
	size_t len2 = strlen(s2);
	char *new_str = malloc(len1 + len2 + 1);
	if (!new_str)
	{
		free(s1);
		return NULL;
	}
	if (s1)
		strcpy(new_str, s1);
	else
		new_str[0] = '\0';
	strcat(new_str, s2);
	free(s1);
	return new_str;
}

int	export_env(char ***env, const char *arg)
{
	int idx;
	char **new_env;
	int count = 0;
	char *key_end;
	size_t key_len;
	char *key;
	char *value;
	int append_mode = 0;

	if (!env || !arg)
		return -1;
	key_end = strchr(arg, '=');
	if (key_end && key_end != arg)
	{
		if (key_end > arg && *(key_end - 1) == '+')
		{
			append_mode = 1;
			key_len = (size_t)(key_end - arg - 1);
		}
		else
			key_len = (size_t)(key_end - arg);
	}
	else
		key_len = strlen(arg);
	key = malloc(key_len + 1);
	if (!key)
		return -1;
	strncpy(key, arg, key_len);
	key[key_len] = '\0';
	value = NULL;
	if (key_end)
		value = (char *)(key_end + 1);
	idx = find_env_key(*env, key);
	if (idx >= 0)
	{
		if (append_mode)
		{
			char *old_val = strchr((*env)[idx], '=');
			char *new_var;

			if (!old_val)
			{
				free((*env)[idx]);
				new_var = malloc(strlen(key) + 1 + strlen(value) + 1);
				if (!new_var)
				{
					free(key);
					return -1;
				}
				sprintf(new_var, "%s=%s", key, value ? value : "");
				(*env)[idx] = new_var;
				free(key);
				return 0;
			}
			char *old_value = old_val + 1;
			char *appended_value = str_join_and_free(strdup(old_value), value ? value : "");
			if (!appended_value)
			{
				free(key);
				return -1;
			}
			new_var = malloc(key_len + 1 + strlen(appended_value) + 1);
			if (!new_var)
			{
				free(appended_value);
				free(key);
				return -1;
			}
			sprintf(new_var, "%s=%s", key, appended_value);
			free(appended_value);
			free((*env)[idx]);
			(*env)[idx] = new_var;
			free(key);
			return 0;
		}
		else
		{
			if (key_end)
			{
				char *new_var = strdup(arg);
				if (!new_var)
				{
					free(key);
					return -1;
				}
				free((*env)[idx]);
				(*env)[idx] = new_var;
			}
			free(key);
			return 0;
		}
	}
	else
	{
		while ((*env) && (*env)[count])
			count++;
		new_env = malloc(sizeof(char *) * (count + 2));
		if (!new_env)
		{
			free(key);
			return -1;
		}
		for (int i = 0; i < count; i++)
			new_env[i] = (*env)[i];
		if (append_mode)
		{
			char *new_var = malloc(key_len + 1 + strlen(value ? value : "") + 2);
			if (!new_var)
			{
				free(new_env);
				free(key);
				return -1;
			}
			sprintf(new_var, "%s=%s", key, value ? value : "");
			new_env[count] = new_var;
		}
		else
		{
			if (key_end)
			{
				new_env[count] = strdup(arg);
				if (!new_env[count])
				{
					free(new_env);
					free(key);
					return -1;
				}
			}
			else
			{
				char *new_var = malloc(key_len + 2);
				if (!new_var)
				{
					free(new_env);
					free(key);
					return -1;
				}
				sprintf(new_var, "%s=", key);
				new_env[count] = new_var;
			}
		}
		new_env[count + 1] = NULL;
		free(*env);
		*env = new_env;
		free(key);
		return 0;
	}
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
				continue ;
			}
			export_env(env, cmd->args[i]);
		}
	}
}
