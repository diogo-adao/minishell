/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:06:40 by ppassos           #+#    #+#             */
/*   Updated: 2025/04/04 11:34:11 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_cut(char *line, int start, int end)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (end - start + 2));
	if (!new)
		return (NULL);
	while (start <= end)
	{
		new[i] = line[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}

t_token	*add_list(int start, int end, int redexist, char *line)
{
	t_token	*new_node;

	if (start > end)
		return (NULL);
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_cut(line, start, end);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
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
	return (new_node);
}

void	add_node(t_token **list, t_token *new_node)
{
	t_token	*temp;

	if (!new_node)
		return ;
	if (!*list)
		*list = new_node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	quote(char *l, int *i)
{
	char	quote;

	quote = '\0';
	while (l[*i] && l[*i] != ' ' && l[*i] != '<'
		&& l[*i] != '>' && l[*i] != '|')
	{
		if (l[*i] == '"' || l[*i] == '\'')
		{
			quote = l[*i];
			(*i)++;
			while (l[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
}

t_token	*creatlist(char *line)
{
	t_aux	a;

	a = (t_aux){0};
	while (line[a.i])
	{
		while (line[a.i] == ' ' || line[a.i] == '\t')
			a.i++;
		a.start = a.i;
		if (line[a.i] == '<' || line[a.i] == '>' || line[a.i] == '|')
		{
			if ((line[a.i] == '<' && line[a.i + 1] == '<')
				|| (line[a.i] == '>' && line[a.i + 1] == '>'))
				a.i++;
			a.new_node = add_list(a.start, a.i, 1, line);
			add_node(&a.list, a.new_node);
			a.i++;
		}
		else
		{
			quote(line, &a.i);
			a.new_node = add_list(a.start, a.i - 1, 0, line);
			add_node(&a.list, a.new_node);
		}
	}
	return (a.list);
}
