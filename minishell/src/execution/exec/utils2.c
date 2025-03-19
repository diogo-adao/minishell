#include "../../../includes/minishell.h"

void free_cmd(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;

    while (cmd)
    {
        if (cmd->args)
        {
            i = 0;
            while (cmd->args[i])
                free(cmd->args[i++]);
            free(cmd->args);
        }
        if (cmd->redir)
        {
            i = 0;
            while (cmd->redir[i])
            	free(cmd->redir[i++]);
            free(cmd->redir);
        }
        tmp = cmd;
        cmd = cmd->next;
        free(tmp);
    }
}

void	signal_handler(int sig)
{
	pid_t	pid;
	int		stat;

	pid = waitpid(-1, &stat, WNOHANG);
	if (sig == SIGINT)
	{
		if (pid == 0)
			printf("\n");
		else
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (pid == 0)
			printf("Quit (core dumped)\n");
		exit_status = 131;
	}
}

int	is_builtin(char *arg)
{
	if ((!ft_strncmp(arg, "echo", 4) && ft_strlen(arg) == 4)
		|| (!ft_strncmp(arg, "env", 3) && ft_strlen(arg) == 3)
		|| (!ft_strncmp(arg, "unset", 5) && ft_strlen(arg) == 5)
		|| (!ft_strncmp(arg, "export", 6) && ft_strlen(arg) == 6)
		|| (!ft_strncmp(arg, "cd", 2) && ft_strlen(arg) == 2)
		|| (!ft_strncmp(arg, "pwd", 3) && ft_strlen(arg) == 3)
		|| (!ft_strncmp(arg, "exit", 4) && ft_strlen(arg) == 4))
		return (1);
	return (0);
}
