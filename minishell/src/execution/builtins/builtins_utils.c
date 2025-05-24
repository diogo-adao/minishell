/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:21:04 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/24 04:27:25 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_cd_error(char *dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, dir, ft_strlen(dir));
	if (access(dir, F_OK) == 0)
		write(2, ": Not a directory\n", 18);
	else
		write(2, ": No such file or directory\n", 28);
}

void	print_getcwd_error(t_cmd *cmd)
{
	write(2, "minishell: cd: error retrieving current directory: getcwd: ", 60);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	cmd->exit = 1;
}
