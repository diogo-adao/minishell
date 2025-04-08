/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literallist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:27:41 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/28 18:21:38 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*removequote(char *line, int t, int i)
{
	int		a;
	int		b;
	int		lenght;
	char	*newline;

	a = 0;
	b = 0;
	lenght = ft_strlen(line);
	newline = malloc(sizeof(char) * (lenght + 1));
	if (!newline)
		return (NULL);
	while (line[a])
	{
		if (a != t && a != i)
		{
			newline[b] = line[a];
			b++;
		}
		a++;
	}
	newline[b] = '\0';
	return (newline);
}

void	dquoteincrement(int *i, int *t, char **new, char **temp)
{
	(*t) = (*i);
	(*i)++;
	while ((*new)[*i] != '"' && (*new)[*i])
		(*i)++;
	*temp = *new;
	*new = removequote(*new, *t, *i);
	free(*temp);
	*temp = NULL;
	*i = *i - 2;
}

void	squoteincrement(int *i, int *t, char **new, char **temp)
{
	(*t) = (*i);
	(*i)++;
	while ((*new)[*i] != 39 && (*new)[*i])
		(*i)++;
	*temp = *new;
	*new = removequote(*new, *t, *i);
	free(*temp);
	*temp = NULL;
	*i = *i - 2;
}

char	*literalparsing(char *new)
{
	int		i;
	int		t;
	char	*temp;

	i = 0;
	t = 0;
	temp = NULL;
	if (new == NULL)
		return (NULL);
	while (new[i])
	{
		if (new[i] == '"' && new[i])
			dquoteincrement(&i, &t, &new, &temp);
		else if (new[i] == 39 && new[i])
			squoteincrement(&i, &t, &new, &temp);
		i++;
	}
	return (new);
}

void	literallist(t_token *list)
{
	if (!list)
		return ;
	while (list)
	{
		if (list->type == STRING)
			list->value = literalparsing(list->value);
		list = list->next;
	}
}
