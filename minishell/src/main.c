/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:43:19 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/21 19:21:23 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_status = 0;

int	validate_shlvl(int shlvl)
{
	if (shlvl < 0)
		return (0);
	if (shlvl >= 1000)
	{
		write(2, "minishell: warning: shell level (", 34);
		write(2, ft_itoa(shlvl), ft_strlen(ft_itoa(shlvl)));
		write(2, ") too high, resetting to 1\n", 27);
		return (1);
	}
	return (shlvl);
}

void	update_shlvl(char ***env)
{
	int		i;
	int		shlvl;
	char	*tmp;
	char	*new;

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi((*env)[i] + 6);
			shlvl = validate_shlvl(shlvl + 1);
			tmp = ft_itoa(shlvl);
			if (!tmp)
				return ;
			new = ft_strjoin("SHLVL=", tmp);
			free(tmp);
			if (!new)
				return ;
			free((*env)[i]);
			(*env)[i] = new;
			return ;
		}
		i++;
	}
}

void	update_shlvl_if_needed(char ***env)
{
	int		i;
	char	*new_env_entry;

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], "MINISHELL_FIRST_RUN=", 20))
		{
			update_shlvl(env);
			return ;
		}
		i++;
	}
	new_env_entry = ft_strdup("MINISHELL_FIRST_RUN=1");
	if (new_env_entry)
	{
		append_to_env(env, new_env_entry);
		free(new_env_entry);
	}
}

int	minishell_loop(char ***env)
{
	t_cmd	cmd;

	cmd.env = env;
	cmd.exit = 0;
	cmd.args = NULL;
	cmd.exit = 0;
	cmd.pid = 0;
	cmd.redir = NULL;
	cmd.next = NULL;
	cmd.prev = NULL;
	while (1)
	{
		cmd.line = readline("minishell> ");
		if (cmd.line == NULL)
		{
			printf("exit\n");
			break ;
		}
		builtins(&cmd);
		add_history(cmd.line);
		free(cmd.line);
	}
	return (cmd.exit);
}

int	main(int ac, char **av, char **envp)
{
	char	**env;
	int		status;

	(void)ac;
	(void)av;
	ft_config_terminal();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	env = ownenvp(envp);
	update_shlvl_if_needed(&env);
	status = minishell_loop(&env);
	free_env(env);
	return (status);
}
