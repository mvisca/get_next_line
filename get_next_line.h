#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

# ifndef NEW_LINE
#  define NEW_LINE '\n'
# endif

# ifndef NULL_END
#  define NULL_END '\0'
# endif

typedef struct  s_file 
{
	char	*l;
	char	*b;
	int     fd;
	int     i;
	int		ini;
}	t_file;

typedef struct	s_node
{
	t_file	*file;
	t_file	*next;	
}	t_node;

char	*get_next_line(int fd);

#endif