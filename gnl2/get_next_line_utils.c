#include "get_next_line.h"

int	ft_strlenc(const char *s, int c)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0' && s[len] != (unsigned char)c)
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] || s[i] != (char))
		i++;
	if (s[i] == (char)c)
		return (&s[i]);
	return(NULL);
}

char    *ft_calloc(size_t nmemb, size_t size)
{
	char    *ptr;
	size_t	nmembxsize;
	size_t	i;

	nmembxsize = nmemb * size;
	if (!nmembxsize)
		nmembxsize = 1;
	ptr = (char *) malloc (nmembxsize);
	i = 0;
	while (ptr && i < nmembxsize + 1)
		ptr[i++] = 0;
	printf ("LEAVING FTCALLOC\n");
	return (ptr);
}

char	*ft_strjoinfree(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1)
		return (NULL);
	new = ft_calloc (1, (ft_strlenc(s1, 0) + ft_strlenc(s2, 0) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	*(new + i) = '\0';
	return (new);
}
