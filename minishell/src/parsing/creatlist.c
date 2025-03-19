/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:06:40 by ppassos           #+#    #+#             */
/*   Updated: 2025/02/11 15:03:59 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
char *ft_cut(char *line, int start, int end)
{
	char *new;
	int i;
	
	i = 0;
	new = malloc(sizeof(char) * (end - start + 2));
	if (!new)
		return(NULL);
	while (start <= end)
	{
		new[i] = line[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return(new);
}
void add_list(int start, int end, t_token **list, int redexist, char *line)
{
    t_token *new_node;

    if (start > end)
        return;
    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return;
    new_node->value = ft_cut(line, start, end);
    if (!new_node->value)
    {
        free(new_node);
        return;
    }
    if (redexist == 0)
        new_node->type = STRING;
    else
    {
        if (line[end] == '|')
            new_node->type = PIPE;
        else
            new_node->type = REDIR;
    }
    new_node->next = NULL;
    if (!*list)
        *list = new_node;
    else
    {
        t_token *temp = *list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

t_token *creatlist(char *line)
{
    t_token *list;
    int i;
    int start;
    char quote;
    int in_quote;

    list = NULL;
    i = 0;
    in_quote = 0;

    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        start = i;
        if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && !in_quote)
        {
            if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
                i++;
            add_list(start, i, &list, 1, line);
            i++;
        }
        else
        {
            while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>' && line[i] != '|')
            {
                if(line[i] == '"' || line[i] == '\'')
                {
                    quote = line[i];
                    i++;
                    while (line[i] != quote)
                        i++;
                }
                i++;
            }
            add_list(start, i - 1, &list, 0, line);
        }
    }
    return list;
}
