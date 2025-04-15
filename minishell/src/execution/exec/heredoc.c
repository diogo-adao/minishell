/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:12 by diolivei          #+#    #+#             */
/*   Updated: 2025/03/18 17:20:22 by ppassos          ###   ########.fr       */
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
		exit_status = 130;
	}
}

int fill_heredoc(int fd, char *del, int *flag)
{
    char *line;

    line = readline("> ");
    if (!line)
    {
        write(2, "minishell: warning: ", 20);
        write(2, "here-document delimited by end-of-file\n", 39);
        return 0;
    }
    if (exit_status == 130)
    {
        (*flag)++;
        free(line);
        return 0;
    }
    if (!ft_strncmp(line, del, ft_strlen(del)) 
        && ft_strlen(line) == ft_strlen(del))
    {
        free(line);
        return 0;
    }
    write(fd, line, ft_strlen(line));
    write(fd, "\n", 1);
    free(line);
    return 1;
}

void heredoc_loop(int fd, char *del, int *flag)
{
    exit_status = 0;
    signal(SIGINT, heredoc_handler);
    signal(SIGQUIT, SIG_IGN);
    while (!(*flag))
    {
        if (!fill_heredoc(fd, del, flag))
            break;
    }
    close(fd);
}

int is_heredoc(t_cmd *cmd)
{
    int i;
    int fd;
    int flag;
    char *tmp;
    char *itoa_j;
    char *joined;
    int j = 0;

    flag = 0;
    while (cmd)
    {
        i = -1;
        while(cmd->redir && cmd->redir[++i])
        {
            if (cmd->redir[i]->flag == HEREDOC)
            {
                itoa_j = ft_itoa(j);
                if (!itoa_j)
                    return (0);
                joined = ft_strjoin("/tmp/.heredoc_", itoa_j);
                free(itoa_j);
                tmp = ft_strdup(joined);
                free(joined);
                fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0664);
                heredoc_loop(fd, cmd->redir[i]->file, &flag);
                free(cmd->redir[i]->file);
                cmd->redir[i]->file = tmp;
            }
            j++;
        }
        cmd = cmd->next;
    }
    return (flag);
}
