/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:11:35 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/09 19:27:40 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * ft_echo() starts by checking if the second argument starts with '-'.
 * check_option() checks if all characters after '-' are 'n'.
 * In the end it prints the tokens passed after "echo" with or without newline
 */

int	check_option(t_data *data)
{
	int	j;
	int	valid_option;

	j = 1;
	valid_option = 1;
	while (data->tokens[1][j])
	{
		if (data->tokens[1][j] != 'n')
		{
			valid_option = 0;
			break ;
		}
		j++;
	}
	return (valid_option);
}

int	ft_echo(t_data *data)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 0;
	newline = 1;
	if (data->tokens[1] && data->tokens[1][0] == '-' && check_option(data))
	{
		newline = 0;
		i++;
	}
	while (i < data->token_count)
	{
		write(1, data->tokens[i], ft_strlen(data->tokens[i]));
		if (i + 1 < data->token_count)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

// Main for testing
/* int main()
{
    char *input;
    t_data data;  // Declare t_data struct
    data.tokens = malloc(100 * sizeof(char *));
    if (!data.tokens)
    {
        perror("Malloc failed");
        return 1;
    }

    while (1) // Infinite loop
    {
        // Display prompt and read input
        input = readline("minishell> ");
        if (!input) // Handle EOF (Ctrl+D)
            break;

        // Add input to history
        add_history(input);

        // Tokenize the input
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL)
        {
            data.tokens[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        data.tokens[i] = NULL; // Null-terminate the tokens array
        data.token_count = i;  // Set the token count

        // If the first token is "echo", call ft_echo
        if (data.tokens[0] && strcmp(data.tokens[0], "echo") == 0)
        {
            ft_echo(&data);  // Call ft_echo with the t_data struct
        }
        else if (strcmp(input, "exit") == 0)
        {
            // Exit condition
            free(input);
            break;
        }

        // Free the allocated memory for the input
        free(input);
    }

    free(data.tokens);  // Free the memory allocated for tokens
    return 0;
} */
