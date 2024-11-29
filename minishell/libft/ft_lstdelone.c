/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:29:47 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/01 18:17:07 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/* void del_content(void *content)
{
	free(content);
}

int main()
{
	t_list *node = malloc(sizeof(t_list));
	int *content = malloc(sizeof(int));
	*content = 42;
	node->content = content;
	node->next = NULL;

	ft_lstdelone(node, del_content);

	// Try to access the content (should cause undefined behavior if deleted)
	int value = *(int*)node->content;

	printf("This line may not be printed if ft_lstdelone works correctly.\n");
	return (0);
} */
