/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:10:37 by diolivei          #+#    #+#             */
/*   Updated: 2025/04/17 15:10:39 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old_ptr, size_t old_len, size_t new_len)
{
	char	*new_ptr;

	new_ptr = malloc(new_len);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, new_len);
	ft_memcpy(new_ptr, old_ptr, old_len);
	free(old_ptr);
	return (new_ptr);
}
