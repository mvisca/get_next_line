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
	while (loop || line)
	{
		loop = 0;
		line = get_next_line(fd);
		if (i++ && !line)
			break ;
		printf("Line %d\n=== %s'\\0' ===\n", i + 1, line);
		free(line);
	}
	printf ("LEAVING MAIN\n");
	close(fd);
	return (0);
}
