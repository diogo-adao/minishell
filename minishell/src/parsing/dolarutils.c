/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:27:42 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/27 15:56:23 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*getpart1(char *part1, char *text, int end)
{
	int	i;

	i = 0;
	if (end == 0)
		return (NULL);
	part1 = malloc(sizeof(char) * (end + 1));
	if (!part1)
		return (NULL);
	while (text[i] && i != end)
	{
		part1[i] = text[i];
		i++;
	}
	part1[i] = '\0';
	return (part1);
}

char	*getpart2(char *part2, char *text, int begin)
{
	int	i;
	int	textlen;

	i = 0;
	textlen = ft_strlen(text);
	textlen = textlen - begin;
	if (text[begin] == '\0')
		return (NULL);
	part2 = malloc(sizeof(char) * (textlen + 1));
	if (!part2)
		return (NULL);
	while (text[begin])
	{
		part2[i] = text[begin];
		i++;
		begin++;
	}
	part2[i] = '\0';
	return (part2);
}

char	*allt(char *p1, char *p2, char *p3)
{
	int		i;
	int		j;
	char	*allt;

	i = 0;
	j = (ft_strlen(p1) + ft_strlen(p2) + 1 + ft_strlen(p3));
	allt = malloc(sizeof(char) * (j));
	j = 0;
	if (!allt)
		return (NULL);
	while (p1[j])
		allt[i++] = p1[j++];
	j = 0;
	while (p2[j])
		allt[i++] = p2[j++];
	j = 0;
	while (p3[j])
		allt[i++] = p3[j++];
	allt[i] = '\0';
	return (allt);
}

char	*combine(char *line, char *expenv, int t, int i)
{
	char	*part1;
	char	*part2;
	char	*newline;

	part1 = getpart1(NULL, line, i);
	part2 = getpart2(NULL, line, (t + i + 1));
	if (expenv == NULL && part1 != NULL && part2 != NULL)
		newline = ft_strjoin(part1, part2);
	if (expenv != NULL && part1 != NULL && part2 != NULL)
		newline = allt(part1, expenv, part2);
	if (expenv != NULL && part1 != NULL && part2 == NULL)
		newline = ft_strjoin(part1, expenv);
	if (expenv != NULL && part1 == NULL && part2 != NULL)
		newline = ft_strjoin(expenv, part2);
	if (expenv == NULL && part1 != NULL && part2 == NULL)
		newline = ft_strdup(part1);
	if (expenv == NULL && part1 == NULL && part2 != NULL)
		newline = ft_strdup(part2);
	if (expenv != NULL && part1 == NULL && part2 == NULL)
		return (ft_copy(expenv));
	if (part1)
		free(part1);
	if (part2)
		free(part2);
	return (newline);
}
