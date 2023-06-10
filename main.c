#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;
	int		loop;

	i = 0;
	loop = 1;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1 && printf ("Open file: error\n")) 
		return (1);
	while (loop)
	{
		printf ("LOOP MAIN\n");
		loop = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("Line %d\n=== %s'\\0' ===\n", i, line);
		i++;
		free(line);
	}
	printf ("LEAVING MAIN\n");
	close(fd);
	return (0);
}
