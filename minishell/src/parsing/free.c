/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:59:10 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/23 16:35:08 by diolivei         ###   ########.fr       */
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
		free(temp->value);
		free(temp);
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	cmda_s(t_cmd **cmd, int *i)
{
	if ((*cmd)->redir)
	{
		while ((*cmd)->redir[*i])
		{
			free ((*cmd)->redir[*i]->file);
			free ((*cmd)->redir[*i]);
			(*i)++;
		}
		free ((*cmd)->redir);
	}
}

void	free_cmda(t_cmd *cmd)
{
	t_cmd		*tmp;
	int			i;

	while (cmd)
	{
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		i = 0;
		cmda_s(&cmd, &i);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

void	free_all(t_token *list, char *line, t_cmd *cmd, int i)
{
	free_listt(list);
	if (line)
		free(line);
	if (i != 0)
		free_cmda(cmd);
}
