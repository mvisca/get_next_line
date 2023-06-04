#include "get_next_line.h"

static char	*str_join_move_free(char *line, char **buffer, int *i)
{
	char	*tmp;
	char	*new;

	tmp = line; 						// bkp de line
	new = ft_substr(*buffer, 0, *i); 	// tomo de buffer desde inicio hasta aparicion de \n
	line = ft_strjoin(line, new);		// line es line + new, vacion la memoria del viejo line
	if (!new || !line)
	{
		free(new);
		free(line);
		return (NULL);
	}
	(*i)++;
	ft_memmove(*buffer, &(*buffer)[(*i)], (BUFFER_SIZE - *i));
	*i = BUFFER_SIZE - *i;				// actualizo valor de i a total del buffer menos el largo del stringo bueno cogido
	free(tmp);							// vacion tmp
	return (line);	
}

char    *get_next_line(int fd)
{
	static char	*buffer;
	static int	i = 0;
	int			readed;
	char		*line;

	if (!buffer)
		buffer = malloc (BUFFER_SIZE + 1);
	if (buffer)
	{
		line = NULL;
		readed = read (fd, &buffer[i], BUFFER_SIZE - i);
		buffer[i + readed] = '\0';
		while (readed > 0)
		{
			i = 0;
			while (buffer[i] && buffer[i] != '\n' && i < BUFFER_SIZE)
				i++;
			if (buffer[i] == '\n' || !buffer[i])
			{
				line = str_join_move_free(line, &buffer, &i);
				if (!line)
					return (NULL);
				return (line);
			}
			else 
			{
				line = ft_strjoin(line, buffer);
				readed = read (fd, &buffer[i], BUFFER_SIZE - 1);
				if (!line || readed <= 0)
					return (NULL);
			}
			i++;
		}
	}
	return (line);
}