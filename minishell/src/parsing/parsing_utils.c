/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:12:42 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/23 18:33:02 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_env_variable(t_expand_ctx ctx, int t)
{
	char	*expenv;
	char	*a;

	expenv = getexp(*ctx.line, t, *ctx.i, ctx.env);
	a = expenv;
	if (expenv)
	{
		expenv = add_fandl(expenv, '"');
		free(a);
	}
	*ctx.line = combine(*ctx.line, expenv, t, *ctx.i);
	free(*ctx.temp);
	*ctx.temp = *ctx.line;
	*ctx.i += ft_strlen(expenv);
	free(expenv);
}

void	handle_last_status(t_cmd *cmd, int status)
{
	int	code;
	int	signo;

	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		if (code == 0)
			code = cmd->exit;
		set_exit_status(code);
	}
	else if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if (signo == SIGINT)
			ft_putstr_fd("\n", 2);
		set_exit_status(128 + signo);
	}
}
