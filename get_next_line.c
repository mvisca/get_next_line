/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:17:35 by mvisca            #+#    #+#             */
/*   Updated: 2023/06/10 20:27:04 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// K_NL (NewLine) '\n'
// K_ES (EndString) '\0'

static char	*free_and_say_null(char *free_me)
{
	free(free_me);
	return (NULL);
}

static char	*read_fd(int fd, char *raw)
{
	char	*buf;
	int		bytes_r;
	
	bytes_r = 1;
	if (ft_strchr(raw, K_NL))
		return (raw);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (free_and_say_null(raw));
	while (bytes_r > 0 && !ft_strchr(raw, K_NL))
	{
		bytes_r = read (fd, buf, BUFFER_SIZE);
		if (bytes_r == -1)
			return (free_and_say_null(buf));
		buf[bytes_r] = 0;
		raw = ft_strjoin_and_free(raw, buf);
		if (!raw)
			return (free_and_say_null(buf));
	}
	return (raw);
}

static char	*split_raw(char *raw)
{
	char	*line;
	int		len;
	int		i;

	len = ft_strlenc(raw, K_NL);
	if (raw[len] == K_NL)
		len++;
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len)
		line[i] = raw[i];
	line[i] = K_ES;
	return (line);
}

static char	*update_raw(char *raw)
{
	char	*new_raw;
	int		start;
	int		end;
	int		j;

	if (!ft_strchr(raw, K_NL))
		return (raw);
	start = ft_strlenc(raw, K_NL) + 1;
	end = ft_strlenc(raw, K_ES);
	new_raw = malloc(sizeof(char) * (end - start));
	if (!new_raw)
		return (NULL);
	j = -1;
	while (start + ++j < end)
		new_raw[j] = raw[start + j];
	new_raw[j] = K_ES;
	return (new_raw);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*raw = NULL;

    line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!raw || (!ft_strchr(raw, K_NL)))
		return (NULL);
	raw = read_fd(fd, raw);
	if (!raw)
		return (NULL);
	if (ft_strchr(raw, K_NL))
		line = split_raw(raw);
	if (!line)
		return (free_and_say_null(raw));
	raw = update_raw(raw);
	if (!raw)
		return (free_and_say_null(line));
	return (line);
}

