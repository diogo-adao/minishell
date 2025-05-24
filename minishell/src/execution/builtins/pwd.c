/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:40 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/24 04:07:10 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	builtin_pwd(char **env)
{
	char	path[1024];
	char	*pwd;

	pwd = ft_getenv("PWD", env);
	if (getcwd(path, sizeof(path)) == NULL)
	{
		printf("%s\n", pwd);
		return ;
	}
	if (errno == ERANGE)
	{
		write(2, "minishell: pwd: cannot access directory: ", 41);
		write(2, "No such file or directory", 25);
	}
	printf("%s\n", path);
}
