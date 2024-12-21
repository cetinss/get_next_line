/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sencetin <sencetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:39:32 by sencetin          #+#    #+#             */
/*   Updated: 2024/12/21 12:02:40 by sencetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*read_file(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!check_nl(str))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
		if (!str)
			return (ft_free(buffer));
	}
	free (buffer);
	return (str);
}

char	*before_nl(char *str)
{
	int		len;
	char	*line;
	int		is_newline;

	if (!str[0])
		return (NULL);
	is_newline = check_nl(str);
	len = 0;
	while (str[len] && str[len] != '\n')
		++len;
	line = malloc(sizeof(char) * (len + is_newline + 1));
	if (!line)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
	{
		line[len] = str[len];
		++len;
	}
	if (is_newline)
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

char	*after_nl(char *str)
{
	int		len;
	int		i;
	char	*new_str;

	len = 0;
	while (str[len] && str[len] != '\n')
		++len;
	if (!str[len])
		return (ft_free(str));
	new_str = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!new_str)
		return (ft_free(str));
	++len;
	i = 0;
	while (str[len])
	{
		new_str[i] = str[len];
		++len;
		++i;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_file(fd, str);
	if (!str)
		return (NULL);
	line = before_nl(str);
	str = after_nl(str);
	return (line);
}
