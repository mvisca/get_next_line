#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (1)
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
	printf ("LEAVING MAIN\n");
	close(fd);
	if (fd == -1)
	{
		printf ("Error de lectura de archivo%c", '\n'); 
		return (1);
	}
	return (0);
}