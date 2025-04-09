/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:04 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/09 20:01:22 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_pid(t_cmd *cmd, char ***env, int (**_pipe)[2], t_token *list, char *line)
{
	int	exit_code;

	if (cmd->pid == 0)
	{
		exit_code = cmd->exit;
		free_all(list, line, cmd, 1);
		free_arr(*env);
		free(*_pipe);
		exit(exit_code);
	}
	if (cmd->pid == 1 && (!ft_strncmp(cmd->args[0], "exit", 4)
			&& ft_strlen(cmd->args[0]) == 4))
	{
		if (cmd->prev || cmd->next)
			return ;
		if (cmd->args[1] && is_numeric(cmd->args[1]))
		{
			if (cmd->args[2])
				return ;
		}
		printf("exit\n");
		exit_code = cmd->exit;
		free_all(list, line, cmd, 1);
		free_arr(*env);
		free(*_pipe);
		exit(exit_code);
	}
}

void	wait_pid(t_cmd *cmd)
{
	int	status;

	status = 0;
	while (cmd)
	{
		if (cmd->next)
			waitpid(cmd->pid, NULL, 0);
		else
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (!exit_status)
					exit_status = cmd->exit;
				return ;
			}
		}
		cmd = cmd->next;
	}
}

void	exec_cmd(t_cmd *cmd, char ***env, int (**_pipe)[2], t_token *list, char *line)
{
	if ((!ft_strncmp(cmd->args[0], "echo", 4)
			&& ft_strlen(cmd->args[0]) == 4))
		builtin_echo(cmd);
	else if ((!ft_strncmp(cmd->args[0], "env", 3)
			&& ft_strlen(cmd->args[0]) == 3))
		builtin_env(*env);
	else if ((!ft_strncmp(cmd->args[0], "unset", 5)
			&& ft_strlen(cmd->args[0]) == 5))
		builtin_unset(cmd, *env);
	else if ((!ft_strncmp(cmd->args[0], "export", 6)
			&& ft_strlen(cmd->args[0]) == 6))
		builtin_export(cmd, env);
	else if ((!ft_strncmp(cmd->args[0], "cd", 2)
			&& ft_strlen(cmd->args[0]) == 2))
		builtin_cd(cmd, env);
	else if ((!ft_strncmp(cmd->args[0], "pwd", 3)
			&& ft_strlen(cmd->args[0]) == 3))
		builtin_pwd();
	else if ((!ft_strncmp(cmd->args[0], "exit", 4)
			&& ft_strlen(cmd->args[0]) == 4))
		builtin_exit(cmd);
	else
		not_builtin(cmd, *env);
	check_pid(cmd, env, _pipe, list, line);
}

void set_cmd(t_cmd *head, t_cmd *cmd, char ***env, int (**_pipe)[2], int i, t_token *list, char *line)
{
    int fd[2];

	fd[0] = dup(STDIN_FILENO);
    fd[1] = dup(STDOUT_FILENO);
	if (cmd->pid == 0)
		pipe_fd(head, cmd, _pipe, i);
    if (exec_redir(cmd))
    {
        if (cmd->args)
        	exec_cmd(cmd, env, _pipe, list, line);
    }
	else
		check_pid(cmd, env, _pipe, list, line);
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}

void    start_execution(t_cmd *cmd, char ***env, t_token *list, char *line)
{
	int (*_pipe)[2];
	int i;
	t_cmd *head;

	head = cmd;
	i = 0;
    signal(SIGQUIT, signal_handler);
	if (is_heredoc(cmd))
    	return ;
    create_pipes(cmd, &_pipe);
    while (cmd)
    {
        if (cmd->args && (!is_builtin(cmd->args[0]) || cmd->next))
		{
			cmd->pid = fork();
			if (ft_strncmp(cmd->args[0], "./minishell", 11) == 0)
			{
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
			}
		}
        else
        	cmd->pid = 1;
        if (cmd->pid == 0 || cmd->pid == 1)
            set_cmd(head, cmd, env, &_pipe, i, list, line);
     	cmd = cmd->next;
		i++;
	}
	close_pipe(head, &_pipe);
	wait_pid(head);
	free(*_pipe);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
