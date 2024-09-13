# Get Next Line

## Overview

This is my get_next_line project. get_next_line reads lines from a file descriptor, one line at a time and handles file I/O and dynamic memory allocation in C.

## Files

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

## The Functions

### `char *get_next_line(int fd)`

- **Description**: Reads a line from the file descriptor `fd`. It reads the line including the terminating `\n` character unless the end of the file does not end with `\n`.
- **Parameters**: 
  - `fd`: The file descriptor to read from.
- **Returns**: A string containing the read line or `NULL` if no more lines are available or an error occurs.

### `char *append_to_line(char *line, const char *buffer, ssize_t len)`

- **Description**: Appends a portion of the buffer to the existing line.
- **Parameters**:
  - `line`: The current line to which content will be appended.
  - `buffer`: The buffer containing new content.
  - `len`: The length of content to append.
- **Returns**: A new dynamically allocated string with the appended content or `NULL` if memory allocation fails.

### `char *process_buffer(char *buffer, int *i, ssize_t bytes, char *line)`

- **Description**: Processes the buffer to extract a line up to the newline character or end of buffer.
- **Parameters**:
  - `buffer`: The buffer holding the read data.
  - `i`: Current index in the buffer.
  - `bytes`: Number of bytes read into the buffer.
  - `line`: The current line to which content will be added.
- **Returns**: The updated line with the new content appended.

### `ssize_t read_into_buffer(int fd, char *buffer, ssize_t *bytes)`

- **Description**: Reads data from the file descriptor into the buffer.
- **Parameters**:
  - `fd`: The file descriptor to read from.
  - `buffer`: The buffer to fill with data.
  - `bytes`: Pointer to store the number of bytes read.
- **Returns**: The number of bytes read or -1 if an error occurs.

## Compilation

To compile the project, use the following command:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o get_next_line
```

## The main() function

To use the `get_next_line` function, include `get_next_line.h` and call the function with a valid file descriptor. Example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    char *line;

    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
```
