#include "get_next_line.h"

char    *free_storage(char *storage)
{
    free(storage);
    storage = NULL;
    return (NULL);
}

size_t  ft_strlen(char *s)
{
    size_t  i;

    i = 0;
    if (!s)
        return (0);
    while (s[i] != 0)
        i++;
    return (i);
}

char    *ft_strjoin(char *s1, char *s2)
{
    size_t  i;
    size_t  c;
    char    *raw;

    if (!s1)
    {
        s1 = malloc(1 * sizeof(char));
        if (!s1)
            return (NULL);
        s1[0] = '\n';
    }
    raw = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!raw)
        return (free_storage(s1));
    i = -1;
    c = 0;
    if (s1)
        while (s1[++i])
            raw[i] = s1[i]; 
    while (s1[++i])
        raw[i++] = s2[c++];
    raw[ft_strlen(s1) + ft_strlen(s2)] = 0;
    free(s1);
    return (raw);
}

char    *ft_strchr(const char *raw, int c)
{
    char *s;
    int i;

    i = 0;
    s = (char *)raw;
    if (!s)
        return (NULL);
    while (s[i])
    {
        if (s[i] == (char)c)
            return(&s[i]);
        i++;
    }
    if (c == '\0')
        return (&s[i]);
    return (NULL);
}