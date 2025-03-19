/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:32:36 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/10 14:08:10 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *getvalue(char *vline)
{
	int start;
	char *value;
	int i;
	
	i = 0;
	start = 0;
	value = NULL;
	while (vline[start] != '=' && vline[start])
		start++;
	if (vline[start] == '\0')
		return (NULL);
	start++;
	value = malloc((ft_strlen(vline) - start + 1) * sizeof(char));
	if (!value)
		return(NULL);
	while (vline[start])
		value[i++] = vline[start++];
	value[i] = '\0';
	return(value);
}
//copia o envp para depois ser editado pelo export
char	**ownenvp(char **envp)
{
	int i;
	int size;
	char **newenvp;

	newenvp = NULL;
	i = 0;
	while(envp[i])
		i++;
	size = i;
	newenvp = malloc((i + 1) * sizeof(char *));
	if (!newenvp)
		return(NULL);
	i = 0;
	while(i < size)
	{
		newenvp[i] = ft_strdup(envp[i]);
		i++;
	}
	newenvp[i] = NULL;
	return(newenvp);
}
int	findequal(char *env)
{
	int i;

	i = 0;
	while (env[i] != '=')
		i++;
	return(i);
}

char *ft_getenv(char *exp, char **env)
{
    size_t len;
    int i;

    if (!exp || !env)
        return (NULL);
    len = strlen(exp);
    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], exp, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1);
        i++;
    }
    return (NULL);
}
