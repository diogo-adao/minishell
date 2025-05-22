/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:59:10 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/22 19:16:51 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_listt(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		temp->value = ft_free(temp->value);
		temp = ft_free(temp);
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		env[i] = ft_free(env[i]);
		i++;
	}
	env = ft_free(env);
}

void	cmda_s(t_cmd **cmd, int *i)
{
	if ((*cmd)->redir)
	{
		while ((*cmd)->redir[*i])
		{
			(*cmd)->redir[*i]->file = ft_free ((*cmd)->redir[*i]->file);
			(*cmd)->redir[*i] = ft_free ((*cmd)->redir[*i]);
			(*i)++;
		}
		(*cmd)->redir = ft_free ((*cmd)->redir);
	}
}

void free_cmda(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;
    t_cmd *first = cmd;

    while (cmd)
    {
        i = 0;
        if (cmd->args)
        {
            while (cmd->args[i])
            {
                cmd->args[i] = ft_free(cmd->args[i]);
                i++;
            }
            cmd->args = ft_free(cmd->args);
        }
        i = 0;
        cmda_s(&cmd, &i);

        tmp = cmd->next;
        if (cmd != first)
            cmd = ft_free(cmd);

        cmd = tmp;
    }
}
void	*ft_free(void *pointer)
{
	if (pointer)
	{
		free(pointer);
		pointer = NULL;
	}
	return (NULL);
}

void	free_all(t_token *list, char *line, t_cmd *cmd, int i)
{
	free_listt(list);
	line = ft_free(line);
	if (i != 0)
		free_cmda(cmd);
}
