/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:26:37 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/01 16:41:31 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (!lst)
		return (0);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

/* int main()
{
    int data = 1;
    int data2 = 2;
    int data3 = 3;

    t_list *head = malloc(sizeof(t_list));
    head->content = &data;
    head->next = NULL;

    t_list *node2 = malloc(sizeof(t_list));
    node2->content = &data2;
    node2->next = NULL;

    head->next = node2;

    t_list *node3 = malloc(sizeof(t_list));
    node3->content = &data3;
    node3->next = NULL;

    node2->next = node3;

    t_list *last = ft_lstlast(head);
    printf("%d\n", *(int *)last->content);
    return (0);
} */
