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

int	export_env(char ***env, const char *arg)
{
    int        idx;
    t_var_data var;
    char      *new_var;

    if (!env || !arg)
        return -1;
    var.key = extract_key(arg, &var.append_mode, &var.value);
    if (!var.key)
        return -1;
    idx = find_env_key(*env, var.key);
    if (idx >= 0)
	{
        var.append_mode = handle_existing(&(*env)[idx], &var, arg);
        free(var.key);
        return var.append_mode;
    }
    new_var = make_new_var(arg, var.key, var.value, var.append_mode);
    if (!new_var)
	{
        free(var.key);
        return -1;
    }
    idx = insert_env_var(env, new_var);
    free(var.key);
    return idx;
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
