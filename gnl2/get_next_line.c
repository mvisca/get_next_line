/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:23:24 by mvisca            #+#    #+#             */
/*   Updated: 2023/06/08 15:25:41 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_read(int fd, char **raw)
{
	int		bread;
	char	*buffer;

	bread = BUFFER_SIZE;
	buffer = (char *) ft_calloc (sizeof(char), (BUFFER_SIZE + 1));
	while (buffer && bread == BUFFER_SIZE && !ft_strchr(*raw, NL))
	{
		bread = read (fd, buffer, BUFFER_SIZE);	
		if (bread < 0)
			return (NULL);
		buffer[bread] = 0;
		*raw = ft_strjoinfree(*raw, buffer);
		if (!*raw || ft_strchr(*raw, NL) || bread < BUFFER_SIZE)
		{
			free (buffer);
			buffer = *raw;
		}
	}
	return (buffer);
}

char	*gnl_extract(char **line, char *raw)
{
	int		i;
	int		end;

	i = 0;
	if (ft_strchr(raw, NL))
		end = ft_strchr(raw, NL) - raw + 1;
	else
		return (raw);
	*line = (char *) ft_calloc(sizeof(char), (end + 1));
	while (*line && raw[i] && i < end - 1)
	{
		(*line)[i] = raw[i];
		i++;
	}
	if (raw[i])
		(*line)[i++] = NL;
	(*line)[i] = 0;
	return (*line);
}

char	*gnl_shift(char *raw)
{
	int 	len;
	int		i;
	char	*new_raw;

	i = 0;
	if (ft_strchr(raw, NL))
		len = ft_strchr(raw, NL) - raw;
	else
		return (NULL);
	new_raw = (char *) ft_calloc(sizeof(char), (len + 1));
	if (!new_raw)
		return (NULL);
	while (raw[len + i + 1])
	{
		new_raw[i] = raw[len + 1 + i];
		i++;
	}
	new_raw[i] = 0;
	return (new_raw);
}

char	*get_next_line(int fd)
{
	static char	*raw = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!raw || (raw && !ft_strchr(raw, NL)))
	{
		gnl_read(fd, &raw);
		if (!raw)
			return (NULL);
	}
	else
		return (raw);
	gnl_extract(&line, raw);
	if (!line)
		return (NULL);
	raw = gnl_shift(raw);
	printf ("gnl raw :%s'.'\n", raw);
	printf ("gnl line:%s'.'\n", line);
	return (line);
	return (NULL);
}
