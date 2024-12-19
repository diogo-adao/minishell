/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:38:03 by ppassos           #+#    #+#             */
/*   Updated: 2024/12/16 15:21:46 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int ac, char **av)
{
    char *l;
	
    av = NULL;
    l = NULL;
    if (ac != 1)
        return(printf("ola"), 0);
    while (1) // Infinite loop
    {
        l = readline("minishell> "); // Display prompt and read input
        printf("antes:%s\n", l);
        // Add input to history
        //add_history(input);
        // Exit condition
        if (l == NULL || ft_strncmp(l, "exit", 4) == 0)
        {
            free(l);
            break;
        }
        else
            builtins(l);
        // Free the allocated memory for the input
        free(l);
    }
    return (0);
}