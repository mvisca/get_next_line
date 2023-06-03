#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

# define BUF_S BUFFER_SIZE

# ifndef NEW_LINE
#  define NEW_LINE '\n'
# endif

# ifndef NULL_END
#  define NULL_END '\0'
# endif

typedef struct  s_file 
{
	char    *b;
	char	*l;
	int     fd;
	int		b_read;
	int     i;
}	t_file;

char	*get_next_line(int fd);

#endif