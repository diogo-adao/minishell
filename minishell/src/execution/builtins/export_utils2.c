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

char *create_appended_var(const char *key, char *old_value, char *value)
{
    char *appended_value;
    char *temp;
    char *new_var;
    char *val_to_use;

    if (value)
        val_to_use = value;
    else
        val_to_use = "";
    appended_value = str_join_and_free(ft_strdup(old_value), val_to_use);
    if (!appended_value)
        return NULL;
    temp = ft_strjoin(key, "=");
    if (!temp)
    {
        free(appended_value);
        return NULL;
    }
    new_var = ft_strjoin(temp, appended_value);
    free(temp);
    free(appended_value);
    if (!new_var)
        return NULL;
    return new_var;
}

int append_with_old(char **var, const char *key, char *value)
{
    char *old_val;
    char *old_value;
    char *new_var;

    old_val = ft_strchr(*var, '=');
    old_value = old_val + 1;
    new_var = create_appended_var(key, old_value, value);
    if (!new_var)
        return -1;
    free(*var);
    *var = new_var;
    return 0;
}

int append_to_var(char **var, const char *key, char *value)
{
    char *old_val;

    old_val = ft_strchr(*var, '=');
    if (!old_val)
        return append_no_old(var, key, value);
    else
        return append_with_old(var, key, value);
}

int replace_var(char **var, const char *arg)
{
    char *new_var;

    new_var = ft_strdup(arg);
    if (!new_var) 
        return -1;
    free(*var);
    *var = new_var;
    return 0;
}

char	*make_new_var(const char *arg, const char *key, char *value, int append_mode)
{
	char	*temp;
	char	*new_var;
	char	*val_to_use;
	int		has_equal;

	temp = NULL;
	new_var = NULL;
	val_to_use = "";
	has_equal = 0;
	if (value)
		val_to_use = value;
	if (ft_strchr(arg, '='))
		has_equal = 1;
	if (append_mode)
	{
		temp = ft_strjoin(key, "=");
		new_var = ft_strjoin(temp, val_to_use);
		free(temp);
	}
	else if (has_equal)
		new_var = ft_strdup(arg);
	else
		new_var = ft_strjoin(key, "=");
	return (new_var);
}