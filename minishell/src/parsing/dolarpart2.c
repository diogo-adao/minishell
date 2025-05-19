/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarpart2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:43:55 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/19 17:32:48 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_double_quotes(int *i, char **line, char **temp, char **env)
{
	(*i)++;
	while ((*line)[*i] != '"' && (*line)[*i])
	{
		if ((*line)[*i] == '$')
			handle_dollar_inside_quotes(i, line, temp, env);
		(*i)++;
	}
}

void	handle_dollar_inside_quotes(int *i, char **l, char **temp, char **env)
{
	int		t;
	char	*expenv;

	t = explen(*l, *i);
	if (t != -2)
	{
		expenv = getexp(*l, t, *i, env);
		*l = combine(*l, expenv, t, *i);
		free (*temp);
		*temp = *l;
		if (expenv)
		{
			(*i) += ft_strlen(expenv) - 1;
			free (expenv);
		}
	}
	else if ((*l)[*i + 1] == '?')
		handle_exit_status(i, l, temp);
}

void	handle_single_quotes(int *i, char **line)
{
	(*i)++;
	while ((*line)[*i] != 39 && (*line)[*i])
		(*i)++;
}

void	handle_dollar_sign(int *i, char **line, char **temp, char **env)
{
	int		t;
	char	*expenv;
	char	*a;

	t = explen(*line, *i);
	if (t != -2)
	{
		expenv = getexp(*line, t, *i, env);
		a = expenv;
		expenv = add_fandl(expenv, '"');
		free(a);
		*line = combine(*line, expenv, t, *i);
		free (*temp);
		*temp = *line;
		(*i) += ft_strlen(expenv) - 1;
		free (expenv);
	}
	else if ((*line)[*i + 1] == '?')
		handle_exit_status(i, line, temp);
	else
		(*i)++;
	(*i)--;
	if (*i == -2)
		(*i) = 0;
}

void	handle_exit_status(int *i, char **line, char **temp)
{
	char	*expenv;

	expenv = ft_itoa(g_exit_status);
	*line = combine(*line, expenv, 1, *i);
	free (*temp);
	*temp = *line;
	if (expenv)
	{
		(*i) += ft_strlen(expenv) - 1;
		free (expenv);
	}
}
