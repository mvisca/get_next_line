#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

#define NL '\n'

char	*get_next_line(int fd);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoinfree(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int     ft_strlen(const char *s);

#endif
