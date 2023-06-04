#include "get_next_line.h"

static char	*get_line(char **line, unsigned char c)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*line)[i] != c && i < BUFFER_SIZE)
		i++;
	if (i == BUFFER_SIZE) // proteccion a quitar
		return (NULL);
	tmp = *line;
	*line = ft_substr(tmp, 0, i);
	free(tmp);
	if (line)
	{
		if (c == NL && !ft_strjoin_at(line, "\0"))
			return (free_all(line, line));
	}
	return (line);
}

static char	*read_file_get_line(char **line, char **buffer, int fd)
{
	int		rdd;

	rdd = 1;
	while (rdd > 0 && !ft_strnchr(*buffer, NL, BUFFER_SIZE)) // custom recibe tamaño base, caracter y tamaño escanear
	{
		rdd = read (fd, *buffer, BUFFER_SIZE);
		if (!ft_strjoin_at(line, *buffer)) // custom recibe y borra inicial, usa temporal y la libera
			return (free_all(buffer, line));
		if (ft_strnchr(*line, NL, BUFFER_SIZE))
		{
			if (!get_line(line, NL))
				return (free_all(buffer, line));
			return (*line);
		}
	}
	if (!get_line(line, 0))
		return (free_all(buffer, line));
	return (*line);
}

static char *start_buffer(int fd, char **buffer)
{
	int	i;

	*buffer = NULL;
	i = 0;
	if (BUFFER_SIZE != 0)
	{
		*buffer = (char *) malloc (sizeof(char) * BUFFER_SIZE) + 1;
		if (*buffer)
		{
			if (read (fd, *buffer, BUFFER_SIZE) < 1)
				return (free_all(buffer, buffer));
			(*buffer)[BUFFER_SIZE] = 0;
		}
	}
	return (*buffer);
}

static char	*free_all(char **b, char **l)
{
	free(*b);
	*b = NULL;
	free(*l);
	*l = NULL;
	return (NULL);
}

char    *get_next_line(int fd)
{
	static char	*buffer = NULL;
	static int	i 		= 0;
	char		*line;
	int			readed;

	line = ft_strdup("");
	if (!buffer && !start_buffer(fd, &buffer))
		return (free_all(&buffer, &line));

	if (!read_file_get_line(fd, &buffer, &line))
		return (free_all(&buffer, &line));

	if (!adjust_buffer(&buffer))
		return (free_all(&buffer, &line));

	return (line);
}