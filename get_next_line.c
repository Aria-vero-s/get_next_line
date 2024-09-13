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


char	*process_buffer(char *buffer, int *buffer_index, ssize_t bytes_in_buffer, char *line)
{
	int	start_index;
	int	line_len;
	int	linebreak_found;

	start_index = *buffer_index;
	while (*buffer_index < bytes_in_buffer && buffer[*buffer_index] != '\n')
		(*buffer_index)++;
	line_len = *buffer_index - start_index;
	linebreak_found = (*buffer_index < bytes_in_buffer && buffer[*buffer_index] == '\n');
	line = append_to_line(line, buffer + start_index, line_len + linebreak_found);
	if (linebreak_found)
		(*buffer_index)++;
	return (line);
}


ssize_t	read_into_buffer(int fd, char *buffer, ssize_t *bytes_in_buffer)
{
	ssize_t bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
	{
		buffer[bytes_read] = '\0';
		*bytes_in_buffer = bytes_read;
	}
	return (bytes_read);
}


char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
	static ssize_t bytes_in_buffer = 0;
	static int buffer_index = 0;
	char *line = NULL;
	ssize_t bytes_read;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_index >= bytes_in_buffer)
		{
			bytes_read = read_into_buffer(fd, buffer, &bytes_in_buffer);
			buffer_index = 0;
			if (bytes_read <= 0)
				break;
		}
		line = process_buffer(buffer, &buffer_index, bytes_in_buffer, line);
		if (!line || buffer[buffer_index - 1] == '\n')
			break;
	}
	return (line);
}

int main()
{
    int fd;
	fd = open("text.txt", O_RDONLY);

    if (fd < 0)
    {
        printf("Error");
        return (1);
    }

	char *line;
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