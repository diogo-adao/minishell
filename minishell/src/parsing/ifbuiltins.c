/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifbuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:29:16 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/22 19:25:37 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_copy(char *line)
{
	int		i;
	int		lenght;
	char	*newline;

	i = 0;
	lenght = ft_strlen(line);
	newline = malloc(sizeof(char) * (lenght + 1));
	while (line[i])
	{
		newline[i] = line[i];
		i++;
	}
	newline[i] = '\0';
	return (newline);
}
void print_cmd_list(t_cmd *cmd)
{
    int i;

    while (cmd)
    {
        printf("Cmd node:\n");
        
        // Imprime se tem env ou não
        if (cmd->env)
            printf("  Env: PRESENT\n");
        else
            printf("  Env: NOT present\n");
        
        // Imprime line, se não for NULL
        if (cmd->line)
            printf("  Line: %s\n", cmd->line);
        else
            printf("  Line: (null)\n");

        // Imprime args
        if (cmd->args)
        {
            printf("  Args:\n");
            i = 0;
            while (cmd->args[i])
            {
                printf("    args[%d]: %s\n", i, cmd->args[i]);
                i++;
            }
        }
        else
            printf("  Args: (null)\n");

        // Imprime se redir existe
        if (cmd->redir)
            printf("  Redir: PRESENT\n");
        else
            printf("  Redir: NOT present\n");

        // Indica se next e prev existem
        printf("  Next: %s\n", (cmd->next) ? "Yes" : "No");
        printf("  Prev: %s\n", (cmd->prev) ? "Yes" : "No");

        printf("\n");

        cmd = cmd->next;
    }
}

void	builtins(t_cmd *exec)
{
	t_token	*list;

	if (!validqn(exec->line))
	{
		exec->exit = 2;
		return ;
	}
	exec->line = dolar(exec);
	if (exec->line == NULL)
		return ;
	list = creatlist(exec->line);
	literallist(list);
	if (!checker_list(list))
	{
		free_all(list, exec->line, exec, 0);
		exec->exit = 2;
		printf("minishell: syntax error near unexpected token\n");
		return ;
	}
	//print_cmd_list(exec);
	exec = execute_p(list, exec); // problema esta a dar aqui podes mecher aqui
	printf("\n\n\n\n\n");
	//print_cmd_list(exec);
	//start_execution(exec, exec->env, list, exec->line);
	free_all(list, exec->line, exec, 1); // da doule free ou n csg dar free dos outro pipes podes mecher aqui
}
