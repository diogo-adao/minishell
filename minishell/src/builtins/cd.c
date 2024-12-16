/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:46 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/16 16:06:50 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * builtin_cd() starts checking if there is an argument to use as a path
 * if don't it just sends the user to the home directory
 * if there is an argument it first checks if it's a valid path by trying to
 * open the directory and then sends the user to the desired path.
 */

int builtin_cd(t_cmd *cmd)
{
	char *path;
	DIR *dir;

	if (!cmd->args[1])
		chdir(getenv("HOME"));
	else if (cmd->args[2])
		printf("bash: cd: too many arguments\n");
	else if (cmd->args[1])
	{
		path = cmd->args[1];
		dir = opendir(path);
		if (dir)
		{
			chdir(path);
			closedir(dir);
		}
		else if (ENOENT == errno)
		{
			printf("bash: cd: %s: No such file or directory\n", path);
			return (0);
		}
	}
	return (0);
}

// Main for testing
/* int main(void)
{
	char *args[] = {"cd", NULL};
	t_cmd cmd = {args, 0, 0, NULL};
	builtin_cd(&cmd);
	return (0);
} */
