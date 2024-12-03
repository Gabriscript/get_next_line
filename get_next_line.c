/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:09:30 by ggargani          #+#    #+#             */
/*   Updated: 2024/12/03 08:51:08 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h" 
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

char		*get_remaining_line(char *str);
char		*get_this_line(char *str);
char		*read_file(int fd, char *buffer);
static char	*read_fails_check(char *buff);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		buffer = read_file(fd, buffer);
		if (!buffer)
		{
			free (buffer);
			return (NULL);
		}
		if (ft_strchr(buffer, '\n') >= 0)
		{
			line = get_this_line(buffer);
			temp = buffer;
			buffer = get_remaining_line(buffer);
			free(temp);
			return (line);
		}
	}
}

char	*read_file(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;
	char	*temp_buffer;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		return (read_fails_check(buffer));
	}
	temp[bytes_read] = '\0';
	if (!buffer)
		buffer = ft_strdup(temp);
	else
	{
		temp_buffer = buffer;
		buffer = ft_strjoin(buffer, temp);
		free(temp_buffer);
	}
	free(temp);
	return (buffer);
}

static char	*read_fails_check(char *buff)
{
	char	*remaining;

	if (buff && *buff)
	{
		remaining = ft_strdup(buff);
		free(buff);
		return (remaining);
	}
	return (NULL);
}

char	*get_this_line(char *str)
{
	char	*line;
	int		len;

	if (!str || !*str)
		return (NULL);
	len = ft_strchr(str, '\n');
	if (len == -1)
		return (ft_strdup(str));
	line = malloc(len + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, str, len + 1);
	line[len + 1] = '\0';
	return (line);
}

char	*get_remaining_line(char *str)
{
	char	*line_remained;
	int		len_to_skip;
	int		len;

	if (!str || !*str)
		return (NULL);
	len_to_skip = ft_strchr(str, '\n');
	if (len_to_skip == -1)
		return (NULL);
	len = ft_strlen(str) - len_to_skip - 1;
	if (len <= 0)
		return (NULL);
	line_remained = malloc(len + 1);
	if (!line_remained)
		return (NULL);
	ft_memcpy(line_remained, str + len_to_skip + 1, len);
	line_remained[len] = '\0';
	return (line_remained);
}
