/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:37:05 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/16 14:51:28 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*string;

	i = 0;
	string = (char *)str;
	while (i < n)
	{
		string[i] = 0;
		i++;
	}
}

/*int main()
{
    char str[] = "42 School ";
    printf("before bzero: %s\n", str);
    ft_bzero(str, 2);
    printf("after bzero: %s\n", str);
    return (0);
}*/
