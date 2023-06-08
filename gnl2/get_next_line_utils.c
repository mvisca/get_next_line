#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

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

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *) malloc (sizeof(char) * (len1 + len2 + 1));
	if (!new || !s1 || !s2)
	{
		free(new);
		return (NULL);
	}
	new[len1 + len2] = 0;
	i = -1;
	while (++i < len1)
		*(new + i) = *(s1 + i);
	i--;
	while (++i - len1 < len2)
		*(new + i) = *(s2 + (i - len1));
	*(new + i) = '\0';
	free(s1);
	return (new);
}