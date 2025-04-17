/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:31 by ppassos           #+#    #+#             */
/*   Updated: 2025/04/17 16:40:55 by ppassos          ###   ########.fr       */
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
