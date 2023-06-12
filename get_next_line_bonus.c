/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:10:11 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/12 18:38:03 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_null_all(char *buf[256])
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (buf[i])
		{
			free(buf[i]);
			buf[i] = NULL;
		}
		i++;
	}
	return (NULL);
}

static char	*read_fd(int fd, char *raw)
{
	char	*buf;
	int		bytes_r;

	bytes_r = 1;
	buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		raw = free_null(raw);
		return (NULL);
	}
	while (bytes_r > 0 && !(ft_strchr(raw, '\n')))
	{
		bytes_r = read (fd, buf, BUFFER_SIZE);
		if (bytes_r == -1)
		{
			buf = free_null(buf);
			raw = free_null(raw);
			return (NULL);
		}
		buf[bytes_r] = 0;
		raw = ft_strjoin_and_free(raw, buf);
	}
	buf = free_null(buf);
	return (raw);
}

static char	*split_raw(char *raw)
{
	char	*line;
	int		len;
	int		i;

	if (raw[0] == 0)
		return (NULL);
	len = ft_strlenc(raw, '\n');
	if (raw[len] == '\n')
		len++;
	line = (char *) malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len)
		line[i] = raw[i];
	line[i] = 0;
	return (line);
}

static char	*update_raw(char *raw)
{
	char	*new_raw;
	int		start;
	int		end;
	int		j;

	start = ft_strlenc(raw, '\n');
	if (!raw[start])
	{
		raw = free_null(raw);
		return (NULL);
	}
	end = ft_strlenc(raw, 0);
	new_raw = (char *) malloc(sizeof(char) * (end - start + 1));
	if (!new_raw)
	{
		raw = free_null(raw);
		return (NULL);
	}
	j = -1;
	while (raw[start + 1 + ++j])
		new_raw[j] = raw[start + 1 + j];
	new_raw[j] = 0;
	raw = free_null(raw);
	return (new_raw);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*raw[256];

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		free_null_all(raw);
		return (NULL);
	}
	if (!raw[fd] || (!ft_strchr(raw[fd], '\n')))
		raw[fd] = read_fd(fd, raw[fd]);
	if (!raw[fd])
		return (NULL);
	line = split_raw(raw[fd]);
	if (!line)
	{
		raw[fd] = free_null(raw[fd]);
		return (NULL);
	}
	raw[fd] = update_raw(raw[fd]);
	return (line);
}
