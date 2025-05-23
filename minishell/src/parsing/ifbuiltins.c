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

void free_all_tokens_and_line(t_token *list)
{
    t_token *tmp;

    while (list)
    {
        tmp = list->next;
        free(list->value);
        free(list);
        list = tmp;
    }
}

void builtins(t_cmd *exec)
{
    t_token *list;
    char    *orig;

    if (!validqn(exec->line))
    {
        exec->exit = 2;
        return;
    }
    orig = exec->line;
    exec->line = dolar(exec);
    free(orig);
    if (!exec->line)
        return;
    list = creatlist(exec->line);
    literallist(list);
    if (!checker_list(list))
    {
        free_all_tokens_and_line(list);
        exec->exit = 2;
        printf("minishell: syntax error near unexpected token\n");
        return;
    }
    execute_p(list, exec);
    start_execution(exec, exec->env, list, exec->line);
    free_all_tokens_and_line(list);
}
