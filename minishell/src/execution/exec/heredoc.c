/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:12 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/01 10:36:43 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_status = 130;
	}
}

int	fill_heredoc(int fd, char *del, int *flag, char ***env)
{
	char	*line;
	char	*expanded;

	line = readline("> ");
	if (!line)
	{
		write(2, "minishell: warning: ", 20);
		write(2, "here-document delimited by end-of-file\n", 39);
		return (0);
	}
	if (g_exit_status == 130)
		return (free(line), (*flag)++, 0);
	if (!ft_strncmp(line, del, ft_strlen(del))
		&& ft_strlen(line) == ft_strlen(del))
		return (free(line), 0);
	expanded = dolar(line, *env);
	free(line);
	line = expanded;
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

void	heredoc_loop(int fd, char *del, int *flag, char ***env)
{
	g_exit_status = 0;
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	while (!(*flag))
	{
		if (!fill_heredoc(fd, del, flag, env))
			break ;
	}
	close(fd);
}

int	process_heredoc(t_redir *redir, int j, int *flag, char ***env)
{
	int		fd;
	char	*tmp;
	char	*itoa_j;
	char	*joined;

	itoa_j = ft_itoa(j);
	if (!itoa_j)
		return (0);
	joined = ft_strjoin("/tmp/.heredoc_", itoa_j);
	free(itoa_j);
	if (!joined)
		return (0);
	tmp = ft_strdup(joined);
	free(joined);
	if (!tmp)
		return (0);
	fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	heredoc_loop(fd, redir->file, flag, env);
	free(redir->file);
	redir->file = tmp;
	return (1);
}

int	is_heredoc(t_cmd *cmd, char ***env)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->redir && cmd->redir[i])
		{
			if (cmd->redir[i]->flag == HEREDOC)
				if (!process_heredoc(cmd->redir[i], j, &flag, env))
					return (0);
			j++;
			i++;
		}
		cmd = cmd->next;
	}
	return (flag);
}
