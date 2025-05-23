/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:29:30 by diolivei          #+#    #+#             */
/*   Updated: 2025/05/23 12:30:17 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	*exit_status_ptr(void)
{
	static int	status = 0;

	return (&status);
}

void	set_exit_status(int new_status)
{
	*exit_status_ptr() = new_status;
}

int	get_exit_status(void)
{
	return (*exit_status_ptr());
}
