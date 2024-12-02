/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 07:39:36 by ggargani          #+#    #+#             */
/*   Updated: 2024/11/26 10:11:38 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include<fcntl.h>
# include<stdlib.h>
# include<unistd.h>
# define BUFFER_SIZE 10

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(const char *s, char c);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*read_file(int fd, char *buffer);
void	*ft_memcpy(void *destination, const void *source, size_t num);
char	*get_this_line(char *str);
char	*get_remaining_line(char *str);

#endif
