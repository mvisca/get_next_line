#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1 && printf ("Open file: error\n")) 
		return (1);
	while (!line)
	{
		printf ("LOOP MAIN\n");
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("Line %d\n=== %s'\\0' ===\n", i, line);
		i++;
		if (line)
		{
			free(line);
			line = NULL;
		}
		else
			break;
	}
	close(fd);
	return (0);
}
