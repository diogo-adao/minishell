/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:25:43 by diolivei          #+#    #+#             */
/*   Updated: 2024/12/16 18:14:51 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_unset(t_cmd *cmd)
{

}

// Main for testing
int main()
{
	char *args[] = {"unset", "TESTE", NULL};
	t_cmd cmd = {args, 0, 0, NULL};
	builtin_unset(&cmd);
	return (0);
}
