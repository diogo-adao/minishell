/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:40:53 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/19 17:37:27 by ppassos          ###   ########.fr       */
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
		return (printf("minishell: syntax error\n"), 0);
	return (1);
}

char	*add_fandl(char *line, char a)
{
	int		i;
	char	*c;

	i = 1;
	c = NULL;
	if (!line)
		return (ft_strdup("\"\""));
	c = malloc(sizeof(char) * (ft_strlen(line) + 3));
	c[i - 1] = a;
	while (line[i - 1])
	{
		c[i] = line[i - 1];
		i++;
	}
	c[i] = a;
	c[i + 1] = '\0';
	return (c);
}
