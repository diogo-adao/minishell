/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:40 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/16 16:05:00 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * builtin_pwd() simply return the result of getcwd() function.
 * if no error is found, it just prints the current working directory.
 */

int builtin_pwd()
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or directory");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

// Main for testing
/* int main()
{
	builtin_pwd();
	return (0);
} */
