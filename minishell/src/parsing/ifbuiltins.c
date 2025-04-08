/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifbuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:29:16 by ppassos           #+#    #+#             */
/*   Updated: 2025/04/08 19:57:39 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_exec(t_cmd *list)
{
	int	i;

	i = 0;
	while (list)
	{
		while (list->args[i])
		{
			printf("argumento[%d]:%s\n", i, list->args[i]);
			i++;
		}
		i = 0;
		while (list->redir && list->redir[i])
		{
			printf("redir->file:%s redir->flag:%d\n", list->redir[i]->file, list->redir[i]->flag);
			i++;
		}
		i = 0;
		printf("exit:%d, pid:%d\n", list->exit, list->pid);
		if (list && list->next)
			list = list->next;
		else
			break ;
		printf("|\n");
	}
}

void	print_tokens(t_token *list)
{
	while (list)
	{
		printf("Value:{%s}, Type:'%d'\n", list->value, list->type);
		list = list->next;
	}
	printf("......FIM DA LISTA......\n");
}

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
		exit_status = 2;
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
		exit_status = 2;
		printf("error\n");
		return ;
	}
	//print_tokens(list);
	exec = execute_p(list);
	//print_exec(exec);
	start_execution(exec, env, list, line);
	free_all(list, line, exec, 1);
}
