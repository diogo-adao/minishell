/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:25 by diolivei          #+#    #+#             */
/*   Updated: 2024/05/02 16:56:16 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*head;

	if (!lst || !f || !del)
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (0);
	head = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = NULL;
	return (head);
}

/* void *transform_content(void *content)
{
	if (content == NULL) {
		return NULL;
}
	char *str = (char *)content;
	char *result = ft_strdup(str);
	for (size_t i = 0; result[i]; i++) {
		result[i] = ft_toupper(result[i]);
	}
	return (result);
}

void free_content(void *content)
{
	free(content);
}

int main()
{
	t_list *lst = ft_lstnew("hello");
	ft_lstadd_back(&lst, ft_lstnew("world"));
	t_list *new_lst = ft_lstmap(lst, transform_content, free_content);

	t_list *ptr = new_lst;
	while (ptr) {
		printf("%s ", (char *)ptr->content);
		ptr = ptr->next;
	}
	printf("\n");

	return 0;
} */
