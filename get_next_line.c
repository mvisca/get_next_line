/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:17:35 by mvisca            #+#    #+#             */
/*   Updated: 2023/06/11 12:28:07 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// K_NL (NewLine) '\n'
// K_ES (EndString) '\0'

static char	*free_null(char *buf)
{
	free(buf);
	buf = NULL;
	return (NULL);
}

static char	*read_fd(int fd, char *raw)
{
	char	*buf;
	int		bytes_r;
	
	bytes_r = 1;
	buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_null(raw));
	while (bytes_r > 0 && !(ft_strchr(raw, K_NL)))
	{
		bytes_r = read (fd, buf, BUFFER_SIZE);
		if (bytes_r == -1)
		{
			free(buf);
			if (raw)
				free(raw);
			return (NULL);
		}
		buf[bytes_r] = K_ES;
		raw = ft_strjoin_and_free(raw, buf);
	}
	free(buf);
	return (raw);
}

static char	*split_raw(char *raw)
{
	char	*line;
	int		len;
	int		i;

	if (!raw || raw[0] == K_ES)
		return (NULL);
	len = ft_strlenc(raw, K_NL);
	if (raw[len] == K_NL)
		len++;
	line = (char *) malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len)
		line[i] = raw[i];
	if (raw[i] == K_NL)
		line[i++] = K_NL;
	line[i] = K_ES;
	return (line);
}

static char	*update_raw(char *raw)
{
	int		end;
	int		start;
	char	*new_raw;
	int		j;

	end = ft_strlenc(raw, K_ES);
	start = ft_strlenc(raw, K_NL);
	if (!raw[start])
		return (free_null(raw));
	new_raw = (char *) malloc(sizeof(char) * (end - start + 1));
	if (!new_raw)
		return (free_null(raw));
	j = -1;
	while (raw[start + 1 + ++j])
		new_raw[j] = raw[start + 1 + j];
	new_raw[j] = K_ES;
	free(raw);
	return (new_raw);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*raw = NULL;

	if (fd < 0 || BUFFER_SIZE < 1)
//		return (free_null(raw));
	{
		free(raw);
		return (NULL);
	}
	if (!raw || (!ft_strchr(raw, K_NL)))
		raw = read_fd(fd, raw);
	if (!raw)
		return (NULL);
	line = split_raw(raw);
	if (!line)
	{
		free(raw);
		raw = NULL;
		return (NULL);
	}
	raw = update_raw(raw);
	return (line);
}

