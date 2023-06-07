#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	char	str[22] = {'H', 'e', 'l', 'l', 'o', '\n', 32, 'w', 'o', 'r', 'l', 'd', '!', '\n', 0};
	int		i;

	line = str;
	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 12)
	{
		printf ("main -- i : %d \n", i);
		line = get_next_line(fd);
		if (!line)
		{
			break ;
		}
		printf("\n === %s'.' ===\n\n", line);
		free(line);
		i ++;
	}
	close(fd);
	if (fd == -1)
	{
		printf ("Error de lectura de archivo%c", '\n'); 
		return (1);
	}
	return (0);
}