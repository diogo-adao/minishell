/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:43:16 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/16 14:55:16 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (ft_isascii(argv[i][j]))
            {
                printf("  Character %d is ascii.\n", j);
            }
            else
            {
                printf("  Character %d is not ascii.\n", j);
            }
        }
    }

    return (0);
}*/
