/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:09:16 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/24 04:42:34 by diolivei         ###   ########.fr       */
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

int insert_env_var(char ***env, char *new_var)
{
    int    count;
    char **new_env;
	int i;

	i = 0;
    count = 0;
    while ((*env) && (*env)[count])
        count++;
    new_env = malloc(sizeof(char *) * (count + 2));
    if (!new_env)
	{ 
    	return -1;
	}
	while (i < count)
	{
		new_env[i] = (*env)[i];
		i++;
	}
    new_env[count] = new_var;
    new_env[count + 1] = NULL;
    free(*env);
    *env = new_env;
    return 0;
}

int	handle_existing(char **env_var, t_var_data *var, const char *arg)
{
    if (var->append_mode)
        return append_to_var(env_var, var->key, var->value);
    else if (var->value)
        return replace_var(env_var, arg);
    return 0;
}