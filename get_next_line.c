/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrecine- <lrecine-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:29:09 by lrecine-          #+#    #+#             */
/*   Updated: 2024/11/06 15:45:55 by lrecine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new_line(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (free(line), NULL);
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!new_line)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		new_line[j++] = line[i++];
	new_line[j] = '\0';
	return (free(line), new_line);
}

char	*ft_next_line(char *line)
{
	int		i;
	char	*next_line;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	next_line = (char *)malloc(i + 1);
	if (!next_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		next_line[i] = line[i];
		i++;
	}
	if (line [i] == '\n')
	{
		next_line[i] = line[i];
		i++;
	}
	next_line[i] = '\0';
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;
	char		*buffer;
	int			read_bytes;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 1;
	if (line == NULL)
		line = ft_strdup("");
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(line), line = NULL);
	while (!ft_strchr(line, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(line), free(buffer), line = NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
	}
	free(buffer);
	if (!line)
		return (NULL);
	next_line = ft_next_line(line);
	line = ft_new_line(line);
	return (next_line);
}
