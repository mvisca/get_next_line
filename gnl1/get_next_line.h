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

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif

// typedef struct  s_file 
// {
// 	char	*l;
// 	char	*b;
// 	int     fd;
// 	int     i;
// 	int		ini;
// }	t_file;

// typedef struct	s_node
// {
// 	t_file	*file;
// 	t_file	*next;	
// }	t_node;