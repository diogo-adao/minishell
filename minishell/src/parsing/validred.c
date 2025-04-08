/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validred.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:28:08 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/27 16:55:13 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
	//ver os seguintes erros:
	//quando > e >> tem nada a esquerda e tem de ter um comando na direita
	//quando | tem nada a direita ou na esquerda
	//quando < tem nada a esquerda
	//quando << tem nada a esquerda
	// se erro retornar 0
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
