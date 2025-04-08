/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:41:05 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/31 17:39:38 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_type(t_token *list)
{
	if (ft_strncmp(list->value, ">", 2) == 0)
		return (OUTPUT);
	if (ft_strncmp(list->value, ">>", 3) == 0)
		return (APPEND);
	if (ft_strncmp(list->value, "<", 2) == 0)
		return (INPUT);
	if (ft_strncmp(list->value, "<<", 3) == 0)
		return (HEREDOC);
	return (0);
}

int	redir_count(t_token *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		if (list && list->type == STRING)
			list = list->next;
		if (list && list->type == REDIR)
		{
			i += 2;
			list = list->next;
			list = list->next;
		}
		if (list && list->type == PIPE)
			break ;
	}
	return (i);
}

int	string_count(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list && list->type == STRING)
		{
			i++;
			list = list->next;
		}
		if (list && list->type == REDIR)
		{
			list = list->next;
			list = list->next;
		}
		if (list && list->type == PIPE)
			break ;
	}
	return (i);
}

char	**arg_fill(char **args, t_token *list, int i)
{
	while (list && !(list->type == PIPE))
	{
		if (list && list->type == STRING)
			args[i++] = ft_strdup(list->value);
		if (list && list->type == REDIR)
			list = list->next;
		if (list && list->next)
			list = list->next;
		else
			break ;
	}
	args[i] = NULL;
	return (args);
}

t_redir	**redir_fill(t_redir **redir, t_token *list, int i)
{
	while (list && !(list->type == PIPE))
	{
		if (list && list->type == REDIR)
		{
			redir[i] = malloc(sizeof(t_redir));
			if (!redir[i])
				return (NULL);
			redir[i]->flag = get_type(list);
			list = list->next;
			redir[i]->file = ft_strdup(list->value);
			i++;
		}
		if (list && list->next)
			list = list->next;
		else
			break ;
	}
	redir[i] = NULL;
	return (redir);
}
