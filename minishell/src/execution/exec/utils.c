/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:28 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/19 18:07:38 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_get_env(char **env, char *key)
{
	int		i;
	int		len;
	char	*pos;

	len = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		pos = ft_strchr(env[i], '=');
		if (pos && (pos - env[i] == len) && !ft_strncmp(env[i], key, len))
			return (ft_strdup(pos + 1));
	}
	return (NULL);
}

void	append_to_env(char ***env, char *new_var)
{
	int	i;

	i = 0;
	while ((*env)[i])
		i++;
	*env = ft_realloc(*env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	(*env)[i] = ft_strdup(new_var);
	(*env)[i + 1] = NULL;
}

char	**remove_from_env(char **env, char *to_remove)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((!ft_strncmp(env[i], to_remove, ft_strlen(to_remove))
				&& env[i][ft_strlen(to_remove)] == '='))
		{
			free(env[i]);
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			return (env);
		}
		i++;
	}
	return (env);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
