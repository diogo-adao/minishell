/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literallist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:27:41 by ppassos           #+#    #+#             */
/*   Updated: 2025/01/20 17:04:07 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*removequote(char *line, int t, int i)
{
	int a;
	int b;
	int lenght;
	char *newline;

	a = 0;
	b = 0;
	lenght = ft_strlen(line);
	newline =  malloc(sizeof(char) * (lenght + 1));
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

char	*literalparsing(char *new)
{
	int i;
	int t;
	char	*temp;

	i = 0;
	t = 0;
	temp = NULL;
	if (new == NULL)
		return (NULL);
	while(new[i])
	{
		if(new[i] == '"' && new[i])
		{
			t = i;
			i++;
			while (new[i] != '"' && new[i])
				i++;
			temp = new;
			new = removequote(new, t, i);
			free(temp);
			temp = NULL;
			i = i - 2;
		}
		else if (new[i] == 39 && new[i])
		{
			t = i;
			i++;
			while (new[i] != 39 && new[i])
				i++;
			temp = new;
			new = removequote(new, t, i);
			free(temp);
			temp = NULL;
			i = i - 2;
		}
		i++;
	}
	return(new);
}
void literallist(t_token *list)
{
	if (!list)
		return;
	while (list)
	{
		if (list->type == STRING)
			list->value = literalparsing(list->value);
		list = list->next;
	}
}
