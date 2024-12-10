/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:26:30 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/01 17:31:30 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!lst || !new)
		return ;
	ptr = new;
	ptr->next = *lst;
	*lst = ptr;
}

/* int main()
{
    int data = 42;
    int data2 = 69;
    int data3 = 100;

    t_list *head = malloc(sizeof(t_list));
    head->content = &data;
    head->next = NULL;

    t_list *ptr = malloc(sizeof(t_list));
    ptr->content = &data2;
    ptr->next = NULL;

    head->next = ptr;

    t_list *new = malloc(sizeof(t_list));
    new->content = &data3;
    new->next = NULL;

    ft_lstadd_front(&head, new);

    ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", *(int *)ptr->content);
        ptr = ptr->next;
    }
    return (0);
} */
