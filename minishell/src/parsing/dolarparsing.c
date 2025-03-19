/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:24:57 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/18 16:32:40 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int endofexp(char	letter)
{
	if (letter == '"' || letter == '$')
		return(1);
	if (letter == '>' || letter == '<')
		return(1);
	if (letter == '|' || letter == ' ')
		return(1);
	if (letter == 39 || letter == '?')
		return(1);
	return (0);
}
int	explen(char	*line, int i)
{
	int	j;
	
	j = 1;
	if (endofexp(line[i + 1]) || !line[i + 1])
		return(-2);
	while(line[i + j] && !endofexp(line[i + j]))
		j++;
	return(j - 1);
}
char *getexp(char *line, int t ,int i, char **env)
{
	int j;
	char	*exp;
	char	*expenv;

	j = 0;
	expenv = NULL;
	exp = malloc(sizeof(char) * (t + 1));
	if (!exp)
        return (NULL);
	i++;
	while (j < t && line[i] != '\0')
    {
        exp[j] = line[i];
        j++;
        i++;
    }
    exp[j] = '\0';
	if (ft_getenv(exp,env) == NULL)
		return(free(exp), NULL);
	expenv = ft_strdup(ft_getenv(exp, env));
	free(exp);
	return(expenv);
}

char *dolarparsing(char *line, char **env)
{
	int i;
	int t;
	char *expenv;
	char *temp;
	int in_squotes = 0;  // Flag para indicar se está dentro de aspas simples
	int in_dquotes = 0;  // Flag para indicar se está dentro de aspas duplas

	i = 0;
	t = 0;
	temp = NULL;
	expenv = NULL;
	line = ft_copy(line);
	temp = line;

	while (line[i])
	{
		// Detecta aspas simples e ignora tudo dentro delas
		if (line[i] == '\'')
		{
			in_squotes = !in_squotes;
			i++;
			continue;
		}

		// Detecta aspas duplas
		if (line[i] == '"')
		{
			in_dquotes = !in_dquotes;
			i++;
			continue;
		}

		// Só expande variáveis se NÃO estiver dentro de aspas simples
		if (line[i] == '$' && !in_squotes)
		{
			t = explen(line, i);
			if (t != -2)
			{
				expenv = getexp(line, t, i, env);
				if (!expenv) // Se a variável não existe, remove ela completamente
					line = combine(line, "", t, i);
				else
					line = combine(line, expenv, t, i);
				
				free(temp);
				temp = line;

				if (line)
				{
					if (expenv)
					{
						i += ft_strlen(expenv);
						free(expenv);
					}
				}
				else
					return (free(expenv), NULL);
			}
			else if (line[i + 1] == '?') // Expande $? corretamente
			{
				expenv = ft_itoa(exit_status);
				line = combine(line, expenv, 1, i);
				free(temp);
				temp = line;
				if (line)
				{
					if (expenv)
					{
						i += ft_strlen(expenv);
						free(expenv);
					}
				}
			}
			else
				i++; // Evita loop infinito se `$` estiver sozinho
		}
		else
			i++; // Avança normalmente
	}
	return (line);
}
char	*dolar(char *line, char **env)
{
	char	*new;

	new = line;
	new = dolarparsing(new, env);
	return(new);
}