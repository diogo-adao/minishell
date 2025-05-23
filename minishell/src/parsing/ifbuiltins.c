/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifbuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:29:16 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/23 17:51:04 by diolivei         ###   ########.fr       */
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

void	builtins(char *line, char ***env)
{
	t_token	*list;
	t_cmd	*exec;

	exec = NULL;
	if (!validqn(line))
	{
		set_exit_status(2);
		return ;
	}
	line = dolar(line, *env);
	if (line == NULL)
		return ;
	list = creatlist(line);
	literallist(list);
	if (!checker_list(list))
	{
		free_all(list, line, exec, 0);
		set_exit_status(2);
		printf("minishell: syntax error near unexpected token\n");
		return ;
	}
	exec = execute_p(list);
	start_execution(exec, env, list, line);
	free_all(list, line, exec, 1);
}
