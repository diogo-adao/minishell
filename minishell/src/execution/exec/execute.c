/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:04 by diolivei          #+#    #+#             */
/*   Updated: 2025/03/18 19:10:32 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_pid(t_cmd *cmd, char ***env)
{
	int	exit_code;

	if (cmd->pid == 0)
	{
		exit_code = cmd->exit;
		free_cmd(cmd);
		free_arr(*env);
		exit(exit_code);
	}
	if (cmd->pid == 1 && (!ft_strncmp(cmd->args[0], "exit", 4)
			&& ft_strlen(cmd->args[0]) == 4))
	{
		exit_code = cmd->exit;
		free_cmd(cmd);
		free_arr(*env);
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

void	exec_cmd(t_cmd *cmd, char ***env)
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
	check_pid(cmd, env);
}

void set_cmd(t_cmd *head, t_cmd *cmd, char ***env, int (**_pipe)[2], int i)
{
    int fd[2];

	fd[0] = dup(STDIN_FILENO);
    fd[1] = dup(STDOUT_FILENO);
    pipe_fd(head, cmd, _pipe, i);
    if (exec_redir(cmd))
    {
        if (cmd->args)
            exec_cmd(cmd, env);
    }
	else
		check_pid(cmd, env);
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}

void    start_execution(t_cmd *cmd, char ***env)
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
        	cmd->pid = fork();
        else
        	cmd->pid = 1;
        if (cmd->pid == 0 || cmd->pid == 1)
            set_cmd(head, cmd, env, &_pipe, i);
     	cmd = cmd->next;
		i++;
	}
	close_pipe(head, &_pipe);
	free(*_pipe);
	wait_pid(head);
}
