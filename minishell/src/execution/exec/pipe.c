/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:21 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/17 15:52:16 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_pipes(t_cmd *cmd, int (**_pipe)[2])
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	*_pipe = malloc(sizeof(int [2]) * i);
	if (!*_pipe)
		return ;
	i = 0;
	tmp = cmd;
	while (tmp->next)
	{
		pipe((*_pipe)[i]);
		tmp = tmp->next;
		i++;
	}
}

void	close_pipe(t_cmd *cmd, int (**_pipe)[2])
{
	int	i;

	i = 0;
	while (cmd && cmd->next)
	{
		if (_pipe && (*_pipe))
		{
			close((*_pipe)[i][0]);
			close((*_pipe)[i][1]);
		}
		cmd = cmd->next;
		i++;
	}
}

void	pipe_fd(t_cmd *head, t_cmd *cmd, int (**_pipe)[2], int i)
{
	if (i > 0)
		dup2((*_pipe)[i - 1][0], 0);
	if (cmd->next)
		dup2((*_pipe)[i][1], 1);
	close_pipe(head, _pipe);
}
