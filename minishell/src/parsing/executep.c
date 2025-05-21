/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:55:46 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/21 19:02:03 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_execute(int count_s, int count_r, t_token **list, t_cmd **exec)
{
	if ((count_s) > 0)
	{
		(*exec)->args = malloc(sizeof(char *) * ((count_s) + 1));
		if (!(*exec)->args)
			return ;
		(*exec)->args = arg_fill((*exec)->args, *list, 0);
	}
	if ((count_r) > 0)
	{
		(*exec)->redir = malloc(sizeof(t_redir *) * ((count_r) / 2 + 1));
		if (!(*exec)->redir)
			return ;
		(*exec)->redir = redir_fill((*exec)->redir, *list, 0);
	}
	while ((*list) && (*list)->type != PIPE)
		(*list) = (*list)->next;
	if ((*list) && (*list)->type == PIPE)
	{
		(*exec)->next = malloc(sizeof(t_cmd));
		if (!(*exec)->next)
			return ;
		ft_memset((*exec)->next, 0, sizeof(t_cmd));
		(*exec)->next->prev = (*exec);
		(*exec) = (*exec)->next;
	}
}

t_cmd	*execute_p(t_token *list, t_cmd *exec)
{
	t_cmd	*head;
	int		count_redir;
	int		count_s;

	if (!exec)
		return (NULL);
	head = exec;
	while (list)
	{
		count_s = string_count(list);
		count_redir = redir_count(list);
		token_execute(count_s, count_redir, &list, &exec);
		if (list && list->next)
			list = list->next;
		else
			break ;
	}
	if (!exec->redir)
		exec->redir = NULL;
	return (head);
}
