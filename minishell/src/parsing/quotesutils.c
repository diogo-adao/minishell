/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:40:53 by ppassos           #+#    #+#             */
/*   Updated: 2024/12/26 11:25:53 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validqn(char *line)
{
	int i;
	int j;
	int u;
	
	i = 0;
	j = 0;
	u = 0;
	while(line[u])
	{
		if (line[u] == '"')
		{
			i++;
			u++;
			while(line[u] != '"' && line[u])
				u++;
			if (line[u] == '"')
                i++;
		}
		else if (line[u] == 39)
		{
			j++;
			u++;
			while (line[u] != 39 && line[u])
				u++;
			if (line[u] == 39)
                j++;
		}
		if(line[u])
			u++;
	}
	if (i % 2 != 0 || j % 2 != 0)
		return (printf("ERROR\n"), 0);
	return(1);
}
