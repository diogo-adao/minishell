/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:31 by ppassos           #+#    #+#             */
/*   Updated: 2025/05/01 10:35:33 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getpwde(void)
{
	char	*cwd;
	char	*a;
	char	*together;

	cwd = getcwd(NULL, 0);
	a = ft_strdup("PWD=");
	together = ft_strjoin(a, cwd);
	free(a);
	free(cwd);
	return (together);
}

char	*ft_getus(void)
{
	char	*cwd;
	char	*a;
	char	*b;
	char	*together;

	cwd = getcwd(NULL, 0);
	a = ft_strdup("_=");
	b = ft_strdup("/./minishell");
	together = allt(a, cwd, b);
	free(a);
	free(b);
	free(cwd);
	return (together);
}

char	**zero_envp(void)
{
	char	**envp;

	envp = malloc((3 + 1) * sizeof(char *));
	envp[0] = ft_getpwde();
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_getus();
	envp[3] = NULL;
	return (envp);
}

int	validskip(char *line, int i)
{
	if (!line[i])
		return (0);
	if (line[i] == '<' || line[i] == ' ' || line[i] == '\t')
		return (0);
	if (line[i] == '>' || line[i] == '|')
		return (0);
	return (1);
}

void	skip_wordh(int *i, char *line)
{
	if (!line[(*i) + 1] || line[(*i) + 1] != '<')
		return ;
	(*i)++;
	(*i)++;
	while (line[(*i)] == ' ' || line[(*i)] == '\t')
		(*i)++;
	while (validskip(line, *i))
	{
		if (line[(*i)] == '"')
		{
			while (line[(*i)] && line[(*i)] != '"')
				(*i)++;
		}
		if (line[(*i)] == 39)
		{
			while (line[(*i)] && line[(*i)] != '"')
				(*i)++;
		}
		(*i)++;
	}
	return ;
}
