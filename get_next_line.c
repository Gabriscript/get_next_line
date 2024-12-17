/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:09:30 by ggargani          #+#    #+#             */
/*   Updated: 2024/12/17 09:26:28 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static char	*update_remaining(char *remaining);
static char	*extract_line(char *remaining);
static char	*fill_buffer(int fd, char *remaining, char *buffer);

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(remaining);
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	remaining = fill_buffer(fd, remaining, buffer);
	free(buffer);
	buffer = NULL;
	if (!remaining)
		return (NULL);
	line = extract_line(remaining);
	remaining = update_remaining(remaining);
	return (line);
}

static char	*fill_buffer(int fd, char *remaining, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(remaining);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!remaining)
			remaining = ft_strdup("");
		temp = remaining;
		remaining = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remaining);
}

static char	*extract_line(char *remaining)
{
	char	*newline_pos;
	char	*line;

	newline_pos = ft_strchr(remaining, '\n');
	if (newline_pos)
		line = ft_substr(remaining, 0, newline_pos - remaining + 1);
	else
		line = ft_strdup(remaining);
	return (line);
}

static char	*update_remaining(char *remaining)
{
	char	*newline_pos;
	char	*new_remaining;

	newline_pos = ft_strchr(remaining, '\n');
	if (newline_pos)
	{
		new_remaining = ft_strdup(newline_pos + 1);
		free(remaining);
		if (new_remaining && *new_remaining == '\0')
		{
			free(new_remaining);
			new_remaining = NULL;
		}
		return (new_remaining);
	}
	free(remaining);
	return (NULL);
}
