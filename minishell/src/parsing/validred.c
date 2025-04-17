/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validred.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:28:08 by ppassos           #+#    #+#             */
/*   Updated: 2025/04/17 16:41:15 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checker_list(t_token *list)
{
	int	pastp;

	pastp = 0;
	if (list && list->type == PIPE)
		return (0);
	while (list)
	{
		if (list->type == PIPE || list->type == REDIR)
		{
			if (list->next == NULL)
				return (0);
			if (pastp == 0 && list->type == PIPE)
				pastp = -1;
			else if ((list->type == REDIR && pastp == -1) || pastp == 0)
				pastp = 1;
			else
				return (0);
		}
		else
			pastp = 0;
		list = list->next;
	}
	return (1);
}
