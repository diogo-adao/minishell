/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:11:20 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/01 14:32:07 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (0);
	head->content = content;
	head->next = NULL;
	return (head);
}

/* int main()
{
    int data = 42;
    t_list *new_node = ft_lstnew(&data);

    if (new_node != NULL)
        printf("New node content: %d\n", *(int *)(new_node->content));
    else
        printf("Failed to create a new node.\n");
    free(new_node);
    return 0;
} */
