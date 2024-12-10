/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:38:03 by ppassos           #+#    #+#             */
/*   Updated: 2024/12/10 15:03:31 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int ac, char **av)
{
    char *input;
	
    av = NULL;
    input = "ok";
    if (ac != 1)
        return(printf("ola"), 0);
    while (1) // Infinite loop
    {
        // Display prompt and read input
        if (!input) // Handle EOF (Ctrl+D)
            break;
        input = readline("minishell> ");
        // Add input to history
        //add_history(input);
        // Exit condition
        if (input == NULL || strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        // Free the allocated memory for the input
        free(input);
    }
    return (0);
}