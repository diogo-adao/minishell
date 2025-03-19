/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:31:16 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/26 16:17:27 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	c = (unsigned char)c;
	while (n && *ptr != c)
	{
		ptr++;
		n--;
	}
	if (n)
		return (ptr);
	else
		return (0);
}

/* int main() {
	const char str[] = "Hello, \0 lol I'm at 42!";
	char c = '\0';
	char *res;

	res = ft_memchr(str, c, 30);
	printf("String after |%c| is - |%s|\n", c, res);
	return (0);
} */
