/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:09:16 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 15:38:47 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
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

char	*str_join_and_free(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
		ft_strcpy(new_str, s1);
	else
		new_str[0] = '\0';
	ft_strcat(new_str, s2);
	free(s1);
	return (new_str);
}

size_t	get_key_len_and_mode(const char *arg, int *append_mode)
{
	char	*key_end;
	size_t	key_len;

	*append_mode = 0;
	key_end = ft_strchr(arg, '=');
	if (key_end && key_end != arg)
	{
		if (key_end > arg && *(key_end - 1) == '+')
		{
			*append_mode = 1;
			key_len = (size_t)(key_end - arg - 1);
		}
		else
			key_len = (size_t)(key_end - arg);
	}
	else
		key_len = ft_strlen(arg);
	return (key_len);
}
