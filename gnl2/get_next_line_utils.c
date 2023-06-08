#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (s && *s != (unsigned char)c)
	{
		if (*s && *(s + 1) == '\0')
		{
			if (((unsigned char)c) == '\0')
				return ((char *)s + 1);
			return (NULL);
		}
		s++;
	}
	return ((char *)s);
}

char	*ft_strjoinfree(char *s1, const char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*new;

	len1 = 0;
	len2 = 0;
	while (s1 && s1[len1])
		len1++;
	while ((s2 && s2[len2]) || len2 < BUFFER_SIZE - 1)
		len2++;
	new = (char *) malloc (sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len1)
		*(new + i) = *(s1 + i);
	i--;
	while (++i - len1 < len2)
		*(new + i) = *(s2 + (i - len1));
	*(new + i) = '\0';
	return (new);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = (void *) malloc (nmemb * size);
	while (ptr && i < (nmemb * size))
		((char *)ptr)[i++] = '\0';
	return (ptr);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}