#include "get_next_line.h"

char    *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	static int	i = 0;
	int         readed;


	readed = read (fd, &buffer[i], BUFFER_SIZE - i);
	

}