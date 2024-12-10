/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:12:29 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/29 18:24:41 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)str;
	i = ft_strlen(ptr);
	ptr += i;
	if (!c)
		return (ptr);
	i += 1;
	while (i--)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		if (i > 0)
			ptr--;
	}
	return (0);
}

/* int main() {
	const char str[] = "Hello, I'm at 42 school!";
	char c = '4';
	char *res;

	res = ft_strrchr(str, c);
	printf("String after last |%c| is - |%s|\n", c, res);
	return (0);
} */
