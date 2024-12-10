/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:46 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/10 18:31:35 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>

int main(void)
{
	char *path = getcwd(NULL, 0);
	printf("%s\n", path);
	chdir("..");
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	return (0);
}
