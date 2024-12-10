/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:45:10 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/29 15:03:42 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*source;
	char	*destino;

	if (!dest && !src)
		return (dest);
	i = 0;
	source = (char *)src;
	destino = (char *)dest;
	while (i < n)
	{
		destino[i] = source[i];
		i++;
	}
	return (dest);
}

/* int main()
{
    printf("After memcpy: %s\n", memcpy("             ", ((void*)0), 17));
	printf("After memcpy: %s\n", ft_memcpy("             ", ((void*)0), 17));
    return (0);
} */
