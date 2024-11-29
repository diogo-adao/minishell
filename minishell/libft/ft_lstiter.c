/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:34:17 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/01 18:45:17 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* void ft_test(void *content)
{
	*(int *)content = 42;
}

int main()
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

	ptr->next = new;

    ft_lstiter(head, ft_test);

    ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", *(int *)ptr->content);
        ptr = ptr->next;
    }
    return (0);
} */
