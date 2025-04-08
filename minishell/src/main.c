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

int main(int ac, char **av, char **envp)
{
    char *l;
    char **env;

    (void)av;
    l = NULL;
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
    env = ownenvp(envp);
    if (ac != 1)
        return(printf("ola"), 0);
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
