/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifbuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:29:16 by ppassos           #+#    #+#             */
/*   Updated: 2024/12/17 17:23:31 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_copy(char *line)
{
	int i;
	int lenght;
	char *newline;
	
	i = 0;
	lenght = ft_strlen(line);
	newline =  malloc(sizeof(char) * (lenght + 1));
	while (line[i])
	{
		newline[i] = line[i];
		i++;
	}
	newline[i] = '\0';
	return (newline);
}
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
        return NULL;
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

char	*literalparsing(char *line)
{
	int i;
	int t;
	char	*new;
	char	*temp;

	i = 0;
	t = 0;
	temp = NULL;
	/*if (!(redirectionok(new)))
		return(free(new), NULL);*/
	new = ft_copy(line);
	new = dolarparsing(new);
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

void	builtins(char *line)
{
	char *new;

	new = line;
	//new = simplequotes(new); // tenho de retirar as " e nao substiruir por expacos
	//printf("depois:%s\n", new);
	if (!validqn(new))
		return;
	new = literalparsing(new); //criar memoria sempre
	if (new == NULL)
		return;
	printf("depois:%s\n", new);
	free(new);
}
// getevn lida coms os $ e caso n encontre retorna null... exemplo de uso: getenv(USER");