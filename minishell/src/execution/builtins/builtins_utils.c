/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:21:04 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/24 04:27:25 by diolivei         ###   ########.fr       */
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

int	find_env_key(char **env, const char *key)
{
	size_t key_len;
	
	key_len = 0;
	while (key[key_len] && key[key_len] != '=' && key[key_len] != '+')
		key_len++;
	for (int i = 0; env[i]; i++)
	{
		if (!ft_strncmp(env[i], key, key_len) && (env[i][key_len] == '=' || env[i][key_len] == '\0'))
			return (i);
	}
	return (-1);
}

char *extract_key(const char *arg, int *append_mode, char **value)
{
    char *key;
    size_t key_len;
    char *key_end;

    *append_mode = 0;
    *value = NULL;
    key_len = get_key_len_and_mode(arg, append_mode);
    key = malloc(key_len + 1);
    if (!key)
        return NULL;
    ft_strncpy(key, arg, key_len);
    key[key_len] = '\0';
    key_end = ft_strchr(arg, '=');
    if (key_end)
        *value = (char *)(key_end + 1);
    return key;
}

int	append_no_old(char **var, const char *key, char *value)
{
	char	*temp;
	char	*new_var;
	char	*val_to_use;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (-1);
	if (value)
		val_to_use = value;
	else
		val_to_use = "";
	new_var = ft_strjoin(temp, val_to_use);
	free(temp);
	if (!new_var)
		return (-1);
	free(*var);
	*var = new_var;
	return (0);
}
