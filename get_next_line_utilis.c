static int	ft_strlen(const char *str)
{
	int len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
	{
		if (*(s + 1) == '\0')
		{
			if (((unsigned char)c) == '\0')
				return ((char *)s + 1);
			return ((void *)0);
		}
		s++;
	}
	return ((char *)s);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	new = (char *) malloc (sizeof(char) * (len1 + len2 + 1));
	if (new)
	{
		while (i < (len1 + len2))
		{
			if (i < len1)
				*(new + i) = *(s1 + i);
			else
				*(new + i) = *(s2 + i - len1);
			i++;
		}
		*(new + i) = '\0';
	}
	return (new);
}
