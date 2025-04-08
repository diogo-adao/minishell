/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:40:53 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/28 14:50:14 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fshort(int *a, char**line, int *u, char c)
{
	(*a)++;
	(*u)++;
	while ((*line)[*u] != c && (*line)[*u])
		(*u)++;
	if ((*line)[*u] == c)
		(*a)++;
}

int	validqn(char *line)
{
	int	i;
	int	j;
	int	u;

	i = 0;
	j = 0;
	u = 0;
	while (line[u])
	{
		if (line[u] == '"')
			fshort(&i, &line, &u, '"');
		else if (line[u] == 39)
			fshort(&j, &line, &u, 39);
		if (line[u])
			u++;
	}
	if (i % 2 != 0 || j % 2 != 0)
		return (printf("ERROR\n"), 0);
	return (1);
}
