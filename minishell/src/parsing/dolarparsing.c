/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:24:57 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/28 17:43:04 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	endofexp(char letter)
{
	if (letter == '"' || letter == '$')
		return (1);
	if (letter == '>' || letter == '<')
		return (1);
	if (letter == '|' || letter == ' ')
		return (1);
	if (letter == 39 || letter == '?')
		return (1);
	return (0);
}

int	explen(char	*line, int i)
{
	int	j;

	j = 1;
	if (endofexp(line[i + 1]) || !line[i + 1])
		return (-2);
	while (line[i + j] && !endofexp(line[i + j]))
		j++;
	return (j - 1);
}

char	*getexp(char *line, int t, int i, char **env)
{
	int		j;
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
	if (ft_getenv(exp, env) == NULL)
		return (free(exp), NULL);
	expenv = ft_strdup(ft_getenv(exp, env));
	free(exp);
	return (expenv);
}

char	*dolarparsing(char *line, char **env)
{
	int		i;
	char	*expenv;
	char	*temp;

	i = 0;
	line = ft_copy(line);
	temp = line;
	expenv = NULL;
	while (line[i])
	{
		if (line[i] == '"')
			handle_double_quotes(&i, &line, &temp, env);
		else if (line[i] == 39)
			handle_single_quotes(&i, &line);
		else if (line[i] == '$')
			handle_dollar_sign(&i, &line, &temp, env);
		if (strlen(line) != (unsigned long)i)
			i++;
	}
	return (line);
}

char	*dolar(char *line, char **env)
{
	char	*new;

	new = line;
	new = dolarparsing(new, env);
	return (new);
}
