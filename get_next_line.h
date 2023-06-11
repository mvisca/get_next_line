#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# define K_NL '\n'
# define K_ES '\0'

char    *get_next_line(int fd);
char    *free_null(char *buf);
int		ft_strlenc(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_and_free(char *s1, const char *s2);

#endif