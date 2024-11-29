/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:33:48 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/01 19:17:48 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!*lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
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
