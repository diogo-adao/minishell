/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:56:06 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/26 19:43:47 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	n;
	char	*p;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	n = ft_strlen(s + start);
	if (n < len)
		len = n;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	while (i < len)
	{
		p[i] = s[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

/* int main() {
	char str[17] = "I'm at 42 school";
	char *substr = ft_substr(str, 18999, 0);

	printf("%s\n", substr);
	return (0);
} */
