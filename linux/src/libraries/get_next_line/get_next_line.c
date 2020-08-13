/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/21 11:20:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_index(const char *str, int c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_line(char **str_read, char **line, int index)
{
	int len;

	*line = ft_substr_gnl(*str_read, 0, index);
	len = ft_strlen_gnl(*str_read + index + 1) + 1;
	ft_memmove_gnl(*str_read, *str_read + index + 1, len);
	if (*str_read && *str_read[0] == '\0')
	{
		free(*str_read);
		*str_read = NULL;
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			byt_read;
	int			index;
	static char	*str_read[FD_SIZE];
	char		buf[BUFFER_SIZE + 1];

	if (line == NULL || fd < 0 || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	if (str_read[fd] && (((index = get_index(str_read[fd], '\n')) != -1)))
		return (get_line(&str_read[fd], line, index));
	while ((byt_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[byt_read] = '\0';
		str_read[fd] = ft_joinstr_gnl(str_read[fd], buf);
		if (((index = get_index(str_read[fd], '\n')) != -1))
			return (get_line(&str_read[fd], line, index));
	}
	if (str_read[fd])
	{
		*line = ft_strdup_gnl(str_read[fd]);
		free(str_read[fd]);
		str_read[fd] = NULL;
	}
	else
		*line = ft_strdup_gnl("");
	return (0);
}
