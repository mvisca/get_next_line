#include "get_next_line.h"

static char	*gnl_adjust_buffer(int fd, char **buffer)
{
	int	i;
	int	b_read;

	if (ft_strchr(*buffer, '\n'))
		i = ft_strchr(*buffer, '\n') - *buffer;
	if (ft_strchr(*buffer, '\0'))
		i = ft_strchr(*buffer, '\0') - *buffer;
	ft_memmove(*buffer, &((*buffer)[i + 1]), BUFFER_SIZE - i);
	b_read = read (fd, &(*buffer)[i], BUFFER_SIZE - i);
	if (b_read == -1)
		return (NULL);
	if (b_read == 0)
	{
		i = 0;
		while (i < BUFFER_SIZE)
			(*buffer)[i++] = '\0';
	}
	return (*buffer);
}

static char	*gnl_get_line(char *fullline)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (!fullline)
		return (NULL);
	if (ft_strchr(fullline, '\n'))
		i = ft_strchr(fullline, '\n') - fullline;
	else
		i = ft_strchr(fullline, '\0') - fullline;
	line = ft_substr(fullline, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*gnl_get_fullline(int fd, char **buffer)
{
	char	*fullline;
	char	*tmp;
	int		b_read;

	fullline = ft_substr(*buffer, 0, BUFFER_SIZE);
	b_read = 1;
	while (b_read > 0 && (!(ft_strchr(fullline, '\n')))) // Cuando vaya quitar parentesis antes de !
	{
		b_read = read (fd, *buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (NULL);
		if (b_read == 0)
			return (fullline);
		tmp = fullline;
		fullline = ft_strjoin(tmp, *buffer);
		free (tmp);
		if (!fullline)
			return (NULL);
	}
	return (fullline);
}

char    *get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*fullline;
	char		*line;
	int			i;

	line = NULL;
	if (BUFFER_SIZE < 1 || read (fd, buffer, 0) != 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *) malloc (sizeof(char) * BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		i = read (fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
	}
	fullline = gnl_get_fullline(fd, &buffer); // GET FULLLINE
	line = gnl_get_line(fullline); // GET LINE
	free(fullline);
	if (!line)
		return (NULL);
	gnl_adjust_buffer(fd, &buffer); // ADJUUST BUFFER
	return (line);
}