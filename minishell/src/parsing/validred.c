/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validred.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:28:08 by ppassos           #+#    #+#             */
/*   Updated: 2025/02/13 09:19:21 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
	//ver os seguintes erros:
	//quando > e >> tem nada a esquerda e tem de ter um comando na direita
	//quando | tem nada a direita ou na esquerda
	//quando < tem nada a esquerda
	//quando << tem nada a esquerda
	// se erro retornar 0
int checker_list(t_token *list)
{
	int pastP;

	pastP = 0;
	if (list && list->type == PIPE)
		return(0);
	while (list)
	{
		if (list->type == PIPE || list->type == REDIR)
		{
			if (list->next == NULL)
				return(0);
			if (pastP == 0 && list->type == PIPE)
				pastP = -1;
			else if ((list->type == REDIR && pastP == -1) || pastP == 0)
				pastP = 1;
			else
				return(0);
		}
		else
			pastP = 0;
		list = list->next;
	}
	return (1);
}
