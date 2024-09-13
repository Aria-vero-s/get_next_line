/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:18:41 by asaulnie          #+#    #+#             */
/*   Updated: 2024/09/13 14:44:46 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*append_to_line(char *line, const char *buffer, ssize_t len)
{
	char	*new_line;
	ssize_t	line_len;

	if (line)
		line_len = ft_strlen(line);
	else
		line_len = 0;
	new_line = malloc(line_len + len + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	if (line)
	{
		ft_memcpy(new_line, line, line_len);
		free(line);
	}
	ft_memcpy(new_line + line_len, buffer, len);
	new_line[line_len + len] = '\0';
	return (new_line);
}

char	*process_buffer(char *buffer, int *i, ssize_t bytes, char *line)
{
	int	start_index;
	int	line_len;
	int	n_found;

	start_index = *i;
	while (*i < bytes && buffer[*i] != '\n')
		(*i)++;
	line_len = *i - start_index;
	n_found = (*i < bytes && buffer[*i] == '\n');
	line = append_to_line(line, buffer + start_index, line_len + n_found);
	if (n_found)
		(*i)++;
	return (line);
}

ssize_t	read_into_buffer(int fd, char *buffer, ssize_t *bytes)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
	{
		buffer[bytes_read] = '\0';
		*bytes = bytes_read;
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	static ssize_t	bytes = 0;
	static int		i = 0;
	char			*line;
	ssize_t			bytes_read;

	line = NULL;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (i >= bytes)
		{
			bytes_read = read_into_buffer(fd, buffer, &bytes);
			i = 0;
			if (bytes_read <= 0)
				break ;
		}
		line = process_buffer(buffer, &i, bytes, line);
		if (!line || buffer[i - 1] == '\n')
			break ;
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
