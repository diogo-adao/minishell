/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:38 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/09 16:26:10 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void no_args(char **env)
{
    int i = 0;

    while (env[i])
    {
        printf("declare -x %s\n", env[i]);
        i++;
    }
}

int is_valid(char *str)
{
    int i;

    i = 0;
    if (!((str[0] >= 'a' && str[0] <= 'z') ||
            (str[0] >= 'A' && str[0] <= 'Z') ||
            str[0] == '_'))
            return (0);
    while (str[++i] && str[i] != '=')
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= '0' && str[i] <= '9') ||
            str[i] == '_'))
            return (0);
    }
    return (1);
}

void    export_env(char ***env, char *arg)
{
    int i;
    char *key;
    char *pos;
    
    pos = ft_strchr(arg, '=');
    if (!pos)
        return;
    i = -1;
    key = ft_substr(arg, 0, pos - arg);
    while ((*env)[++i])
    {
        if (!ft_strncmp((*env)[i], key, pos - arg) && (*env)[i][pos - arg] == '=')
        {
            free((*env)[i]);
            (*env)[i] = arg;
            free(key);
            return ;
        }
    }
    free(key);
    append_to_env(env, arg);
}

void    builtin_export(t_cmd *cmd, char ***env)
{
    int i;

    i = 0;
    if (!cmd->args[1])
        no_args(*env);
    else
    {
        while (cmd->args[++i])
        {
            if (!is_valid(cmd->args[i]))
            {
                ft_putstr_fd("minishell: export: ", 2);
                ft_putstr_fd(cmd->args[i], 2);
                ft_putstr_fd(": not a valid identifier\n", 2);
                cmd->exit = 1;
                break ;
            }
            if (ft_strchr(cmd->args[i], '='))
                export_env(env, cmd->args[i]);
        }
    }
}
