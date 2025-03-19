/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:02:22 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/22 19:41:14 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* void uppercase(unsigned int, char *ch)
{
    *ch = ft_toupper(*ch);
}

int main()
{
    char str[] = "Hello";
    ft_striteri(str, uppercase);
    printf("%s\n", str);
    return (0);
} */
