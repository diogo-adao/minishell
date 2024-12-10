#include "../../includes/minishell.h"

int main(void)
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
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        // Free the allocated memory for the input
        free(input);
    }
	return (0);
}
