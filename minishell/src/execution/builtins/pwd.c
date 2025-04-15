/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:40 by diolivei          #+#    #+#             */
/*   Updated: 2025/03/10 14:46:02 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void builtin_pwd()
{
	char path[1024];

	getcwd(path, sizeof(path));
	if (errno == ERANGE)
		write(2, "minishell: pwd: cannot access directory: No such file or directory", 66);
	printf("%s\n", path);
}
