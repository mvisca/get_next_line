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
		*raw = ft_strjoinfree(raw, buffer);
		if (!*raw || ft_strchr(*raw, NL) || bread < BUFFER_SIZE)
		{
			free (buffer);
			buffer = *raw;
		}
	}
	return (buffer);
}

char	*gnl_extract(char *raw)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (raw[len] && raw[len] != NL)
		len++;
	if (raw[len] == NL)
		len++;
	line = (char *) ft_calloc(sizeof(char) * (len + 1));
	while (line && raw[i] && i < len)
	{
		line[i] = raw[i];
		i++;
	}
	return (line);
}

char	*gnl_shift(char **raw)
{
	int 	len;
	int		i;
	char	new_raw;

	len = 0;
	i = 0;
	while (*raw[len] && *raw[len] != NL)
		len++;
	if (*raw[len] == NL)
		len++;
	new_raw = (char *) ft_calloc(sizeof(char), len + 1);
	while (new_raw && i < len)
	{
		new_raw[i] == *raw[i];
		i++;
	}
	free(*raw);
	return (new_raw);
}
char	*get_net_line(int fd)
{
	static char	*raw = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read (fd, raw, 0))
		return (NULL);
	if (!raw || ft_strchr(raw, NL))
	{
		raw = gnl_read(fd, &raw);
		if (!raw)
			return (NULL);
		line = gnl_extract(&raw);
		if (!line)
			return (NULL);
		raw = gnl_shift(raw);
		if (!raw)
			return (NULL);
	}
	else if (ft_strchr(raw, '\0'))
		return (raw);
	else 
		return (NULL);
}
