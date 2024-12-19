/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:40:53 by ppassos           #+#    #+#             */
/*   Updated: 2024/12/19 11:43:23 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int endofexp(char	letter)
{
	if (letter == '"' || letter == '$' || letter == ' ')
		return(0);
	if (letter == '|' || letter == '>' || letter == '<')
		return(0);
	if (letter == 39)
		return(0);
	return (1);
}
int	explen(char	*line, int i)
{
	int	j;
	
	j = 0;
	i++;
	if(!line[i + j])
		return(-1);
	while(line[i + j])
	{
		if(endofexp(line[i + j]))
		{
			j--;
			break;
		}
		j++;
	}
	return(j);
}
char *getexp(char *line, int t ,int i)
{
	//fazer allocacao de memoria para a string com o conteudo de $''
	// depos getenv(sting)
	//verificar se da null ou nao
	//mandar
}
char *combine(char *line, char *expenv, int t, int i)
{
	//juntar as partes que n fazem parte do $ com o valor de $
}
char *dolarparsing(char *line)
{
	int i;
	int t;
	int	expvoflen;
	char *expenv;
	char *temp;

	i = 0;
	t = 0;
	while(line[i])
	{
		if(line[i] = '"')
		{
			i++;
			while(line[i] != '"' && line[i])
			{
				if (line[i] == '$')
				{
					t = explen(line, i);
					if(t = -1)
						return(printf("ERROR"), NULL);
					expenv = getexp(line, t, i);
					expvoflen = ft_strlen(expenv);
					temp = line;
					line = combine(line, expenv, t, i);
					free(temp);
					i = i + expvoflen - t; //tem de ser o tamanho do valor de $ - $ sem o valor e + line
				}
				i++;
			}
		}
		if(line[i] == 39)
		{
			i++;
			while(line[i] != 39 && line[i])
				i++;
		}
		if (line[i] == '$')
		{
			i++;
			t = explen(line, i);
			expenv = getexp(line, t, i);
			expvoflen = ft_strlen(expenv);
			temp = line;
			line = combine(line, expenv, t, i);
			free(temp);
			i = i + expvoflen - t;
		}
		i++;
	}
	return(line);
	//verificar se o $ esta fora dos '';
	//depois que encontrar igualar uma string para mandar a funcao getenv;
	//verificar se retorna null ou nao;
	//juntar o resultado da string getenv com a string normal sem o $;
}
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
