/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarpart2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:43:55 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/23 18:13:26 by diolivei         ###   ########.fr       */
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
	int				t;
	t_expand_ctx	ctx;

	ctx.i = i;
	ctx.line = line;
	ctx.temp = temp;
	ctx.env = env;
	t = explen(*line, *i);
	if (t != -2)
		expand_env_variable(ctx, t);
	else if ((*line)[*i + 1] == '?')
		handle_exit_status(i, line, temp);
	else
		(*i)++;
	(*i)--;
	if (*i == -2)
		*i = 0;
}

void	handle_exit_status(int *i, char **line, char **temp)
{
	char	*expenv;
	int		status;

	status = get_exit_status();
	expenv = ft_itoa(status);
	*line = combine(*line, expenv, 1, *i);
	free (*temp);
	*temp = *line;
	if (expenv)
	{
		(*i) += ft_strlen(expenv) - 1;
		free (expenv);
	}
}
