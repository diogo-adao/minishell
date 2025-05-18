/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:43 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/17 15:28:16 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	search_env(char *env, char *str)
{
	int	i;
	
	i= 0;
	while (env[i] && str[i] && env[i] != '=')
	{
		if (env[i] != str[i])
			return (0);
		i++;
	}
	return (str[i] == '\0' && (env[i] == '\0' || env[i] == '='));
}

void	builtin_unset(t_cmd *cmd, char **env)
{
	int	i;
	int	j;
	int	k;

	k = 1;
	while (cmd->args && cmd->args[k])
	{
		i = 0;
		while (env[i])
		{
			if (search_env(env[i], cmd->args[k]) == 1)
			{
				free(env[i]);
				j = i;
				while (env[j])
				{
					env[j] = env[j + 1];
					j++;
				}
			}
			else
				i++;
		}
		k++;
	}
}
