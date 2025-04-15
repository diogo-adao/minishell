/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:43:19 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/08 18:43:21 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exit_status;

void	update_shlvl(char ***env)
{
	int		i;
	int		shlvl;
	char	*tmp;
	char	*new;

	i = 0;
	while ((*env)[i++])
	{
		if (!ft_strncmp((*env)[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi((*env)[i] + 6) + 1;
			if (shlvl < 0)
				shlvl = 0;
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
	}
}

void update_shlvl_if_needed(char ***env)
{
    int i;
    char *new_env_entry;

    i = 0;
    while ((*env)[i])
    {
        if (!ft_strncmp((*env)[i], "MINISHELL_FIRST_RUN=", 20))
        {
            update_shlvl(env);
            return;
        }
        i++;
    }
    if ((new_env_entry = ft_strdup("MINISHELL_FIRST_RUN=1")))
    {
        append_to_env(env, new_env_entry);
        free(new_env_entry);
    }
}

int main(int ac, char **av, char **envp)
{
    char *l;
    char **env;

    (void)av;
    (void)ac;
    l = NULL;
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
    env = ownenvp(envp);
    update_shlvl_if_needed(&env);
    while (1)
    {
        l = readline("minishell> ");
        if (l == NULL)
        {
            printf("exit\n");
            free(l);
            break;
        }
        else
        {
            builtins(l, &env);
            add_history(l);
        }
        free(l);
    }
    free_env(env);
    return (0);
}
