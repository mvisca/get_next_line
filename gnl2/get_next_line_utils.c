#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
	{
		if (*(s + 1) == '\0')
		{
			if (((unsigned char)c) == '\0')
				return ((char *)s + 1);
			return (NULL);
		}
		s++;
	}
	return ((char *)s);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	len = 0;
	while (s[len])
		len++;
	dup = (char *) malloc (sizeof(char) * (len + 1));
	if (dup)
	{
		i = 0;
		while (*(s + i))
		{
			*(dup + i) = *(s + i);
			i++;
		}
		*(dup + i) = '\0';
	}
	return (dup);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		i;
	size_t		slen;

	i = 0;
	slen = 0;
	while (s[slen])
		slen++;
	if (slen == 0 || slen < start)
		return (ft_strdup(""));
	if (slen < start + len)
		len = slen - start;
	sub = (char *) malloc (sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len && (unsigned char) s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	if (sub[i])
		sub[i] = '\0';
	return (sub);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else if ( dest > src)
	{
		if (n > 0)
		{
			while ( dest > src && n-- > 0)
			{
				n--;
				((unsigned char *)dest)[n] = ((unsigned char *) src)[n];
			}
		}
	}
	return (dest);
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
		*(new + i) = *(s2 + i - len1);
	*(new + i) = '\0';
	free(s1);
	return (new);
}

void	ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = (void *) malloc (nmemb * size);
	while (ptr && i < (nmemb * size))
		ptr[i++] = '\0';
	return (ptr);
}