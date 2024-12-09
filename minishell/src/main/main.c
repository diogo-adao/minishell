/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:53:11 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/09 16:19:22 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char *argv[])
{
	char *input;

    while (1) // Infinite loop
    {
        // Display prompt and read input
        input = readline("minishell> ");
        if (!input) // Handle EOF (Ctrl+D)
            break;

        // Add input to history
        add_history(input);

        // Exit condition
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        // Free the allocated memory for the input
        free(input);
    }
	return (0);
}
