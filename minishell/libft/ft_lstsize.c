/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:26:43 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/01 17:32:58 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*ptr;

	if (!lst)
		return (0);
	ptr = lst;
	count = 0;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
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

    int n = ft_lstsize(head);
    printf("There is %d nodes\n", n);
    return (0);
} */
