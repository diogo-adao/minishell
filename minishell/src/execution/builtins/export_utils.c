#include "../../../includes/minishell.h"

void	sort_env(char **env)
{
	int		i;
	int		j;
	size_t	len_i;
	size_t	len_j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			len_i = ft_strlen(env[i]);
			len_j = ft_strlen(env[j]);
			if (ft_strncmp(env[i], env[j], len_i > len_j ? len_i : len_j) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**copy_env(char **env)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;
	while (env[len])
		len++;
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}


void	print_export(char *str)
{
	char	*eq;

	write(1, "declare -x ", 11);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		write(1, str, eq - str + 1);
		write(1, "\"", 1);
		write(1, eq + 1, ft_strlen(eq + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
}

char	*find_env_value(char **env, char *key)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (NULL);
}

void	handle_append(char ***env, char *key, char *pos)
{
	char	*old;
	char	*joined;
	char	*temp;
	char	*full;

	old = find_env_value(*env, key);
	if (old)
		joined = ft_strjoin(old, pos + 2);
	else
		joined = ft_strdup(pos + 2);
	temp = ft_strjoin(key, "=");
	full = ft_strjoin(temp, joined);
	free(temp);
	free(joined);
	if (update_env(env, key, ft_strdup(full), ft_strlen(key)))
	{
		free(full);
		return ;
	}
	append_to_env(env, full);
	free(full);
}
