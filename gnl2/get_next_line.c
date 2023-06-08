/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:23:24 by mvisca            #+#    #+#             */
/*   Updated: 2023/06/08 17:00:07 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_read(int fd, char **raw)
{
	int		bread;
	char	*buffer;

	bread = 1;
	buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bread > 0 && !ft_strchr(*raw, NL))
	{
		bread = read (fd, buffer, BUFFER_SIZE);	
		if (bread == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bread] = 0;
		*raw = ft_strjoinfree(*raw, buffer);
	}
	free (buffer);
	return (*raw);
}

char	*gnl_extract(char **line, char **raw)
{
	int		i;
	int		end;

	i = 0;
	if (!*raw)
		return (NULL);
	if (ft_strchr(*raw, NL))
	{
		end = ft_strchr(*raw, NL) + 1 - *raw;
		*line = (char *) malloc (sizeof(char) * (end + 1));
		if (!line)
			return (NULL);
		while ((*raw)[i] && i < end - 1)
		{
			(*line)[i] = (*raw)[i];
			i++;
		}
		if ((*raw)[i])
			(*line)[i++] = NL;
		(*line)[i] = 0;
		return (*line);
	}
	return (*raw);
}

char	*gnl_shift(char *raw)
{
	int		i;
	int 	len_n;
	int		n_len;
	char	*new_raw;

	i = 0;
	if (!ft_strchr(raw, NL))
		return (raw);
	len_n = ft_strchr(raw, NL) - raw;
	n_len = ft_strlen(raw) - len_n;
	new_raw = (char *) malloc(sizeof(char) * (n_len + 1));
	if (!new_raw)
		return (NULL);
	while (raw[len_n + 1 + i])
	{
		new_raw[i] = raw[n_len + 1 + i];
		i++;
	}
	new_raw[i] = 0;
	free(raw);
	return (new_raw);
}

char	*get_next_line(int fd)
{
	static char	*raw = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	raw = gnl_read(fd, &raw);
	if (!raw)
		return (NULL);
	line = gnl_extract(&line, &raw);
	raw = gnl_shift(raw);
	return (line);
}
