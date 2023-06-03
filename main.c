#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	char	str[22] = {'H', 'e', 'l', 'l', 'o', NULL_END, 32, 'w', 'o', 'r', 'l', 'd', '!', NEW_LINE, NULL_END};
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 10)
	{
		line = get_next_line(fd);
//		if (!line)
//			break ;
		printf("%s'.' %c", line, NEW_LINE);
		free(line);
		i ++;
	}
	close(fd);
	if (fd == -1)
	{
		printf ("Error de lectura de archivo%c", NEW_LINE); 
		return (1);
	}
	return (0);
}