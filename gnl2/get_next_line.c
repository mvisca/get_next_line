/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:23:24 by mvisca            #+#    #+#             */
/*   Updated: 2023/06/08 22:44:06 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_free(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

static char	*gnl_read(int fd, char *raw)
{
	int		bread;
	char	*buffer;

	bread = 1;
	buffer = (char *) ft_calloc (sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_free(raw));
	while (bread > 0 && !ft_strchr(raw, '\n'))
	{
		bread = read (fd, buffer, BUFFER_SIZE);	
		if (bread == -1)
		{
			free(buffer);
			if (raw)
				free(raw);
			return (NULL);
		}
		buffer[bread] = 0;
		printf("HOLA read buffer :%s\n", buffer);
		raw = ft_strjoinfree(raw, buffer);
		printf("HOLA read raw :%s\n", raw);
		
	}
	free (buffer);
	buffer = NULL;
	return (raw);
}

char	*gnl_extract(char *raw)
{
	int		i;
	int		end;
	char	*line;
	
	if (!raw[0])
		return (NULL);
	end = ft_strlenc(raw, '\n');
	if (raw[end] == '\n')
		end++;
	line = (char *) ft_calloc (sizeof(char), (end + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (raw[i] && raw[i] != '\n')
	{
		line[i] = raw[i];
		i++;
	}
	if (raw[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*gnl_shift(char *raw)
{
	char	*new_raw;
	int		i;
	int 	len;

	len = ft_strlenc(raw, '\n');
	if (!raw[len])
	{
		free(raw);
		return (NULL);
	}
	new_raw = (char *) ft_calloc (sizeof(char), (ft_strlenc(raw, 0) - len + 1));
	if (!new_raw)
	{
		free(raw);
		return (NULL);
	}
	len++;
	i = 0;
	while (raw[len])
		new_raw[i++] = raw[len++];
	new_raw[i] = 0;
	free(raw);
	return (new_raw);
}

char	*get_next_line(int fd)
{
	static char	*raw = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		free (raw);
		return (NULL);
	}
	if (!raw || (raw && !ft_strchr(raw, '\n')))
		raw = gnl_read(fd, raw);
	if (!raw)
		return (NULL);
	printf("HOLA: raw: %s\n", raw);
	line = gnl_extract(raw);
	if (!line)
	{
		free(raw);
		raw = NULL;
		return (NULL);
	}	
	raw = gnl_shift(raw);
	return (line);
}
