#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

size_t	ft_strlen(char *s);
char	*ft_strchr(const char *raw, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*free_storage(char *storage);
char	*get_next_line(int fd);

#endif