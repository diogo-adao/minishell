/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:24 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/23 12:37:52 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_error(t_cmd *cmd)
{
	if (errno == EACCES)
		write(2, "minishell: Permission denied\n", 29);
	else
		write(2, "minishell: No such file or directory\n", 38);
	cmd->exit = 1;
	return (0);
}

int	file_open(t_cmd *cmd, int *input, int *output, int i)
{
	if (cmd->redir[i]->flag == INPUT || cmd->redir[i]->flag == HEREDOC)
	{
		*input = open(cmd->redir[i]->file, O_RDONLY);
		if (*input == -1)
		{
			handle_error(cmd);
			cmd->exit = 1;
			return (0);
		}
	}
	else if (cmd->redir[i]->flag == OUTPUT)
		*output = open(cmd->redir[i]->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else if (cmd->redir[i]->flag == APPEND)
		*output = open(cmd->redir[i]->file,
				O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (*output == -1)
	{
		handle_error(cmd);
		cmd->exit = 1;
		return (0);
	}
	return (1);
}

int	exec_redir(t_cmd *cmd)
{
	int	i;
	int	input;
	int	output;

	i = 0;
	output = 0;
	while (cmd->redir && cmd->redir[i])
	{
		if (!file_open(cmd, &input, &output, i))
			return (0);
		if (cmd->redir[i]->flag == INPUT || cmd->redir[i]->flag == HEREDOC)
		{
			dup2(input, 0);
			close(input);
			if (cmd->redir[i]->flag == HEREDOC)
				unlink(cmd->redir[i]->file);
		}
		else if (cmd->redir[i]->flag == OUTPUT || cmd->redir[i]->flag == APPEND)
		{
			dup2(output, 1);
			close(output);
		}
		i++;
	}
	return (1);
}
