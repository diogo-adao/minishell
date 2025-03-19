/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:19:59 by diolivei          #+#    #+#             */
/*   Updated: 2024/04/16 14:53:51 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/*int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (ft_isalnum(argv[i][j]))
            {
                printf("  Character %d is alphanumeric.\n", j);
            }
            else
            {
                printf("  Character %d is not alphanumeric.\n", j);
            }
        }
    }
    return (0);
}*/
