/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:03:46 by diolivei          #+#    #+#             */
/*   Updated: 2024/07/16 15:28:07 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_collect(int fd, char *buf, char *save)
{
	int		chars_read;
	char	*tmp;

	chars_read = 1;
	while (chars_read)
	{
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read == -1)
			return (NULL);
		if (chars_read == 0)
			break ;
		buf[chars_read] = '\0';
		if (!save)
			save = ft_strdup("");
		tmp = save;
		save = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (save);
}

static char	*ft_newline(char *line)
{
	int		i;
	char	*save;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (0);
	save = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*save == '\0')
	{
		free(save);
		save = NULL;
	}
	line[i + 1] = '\0';
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = ft_collect(fd, buf, save);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	save = ft_newline(line);
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>
int main()
{
    int fd = open("teste.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
        printf("%s", line);
    return (0);
} */
