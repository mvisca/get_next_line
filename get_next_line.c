#include "get_next_line.h"

/*###############################################
#												#
#	UTILS FILE									#
#												#
###############################################*/

char	*ft_strjoin(char *s1, const char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*new;

	len1 = 0;
	len2 = 0;
	while (s1 && s1[len1])
		len1++;
	while (s2 && s2[len2] || len2 < BUF_S - 1)
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
	return (new);
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
		return (ft_strjoin("", ""));
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

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	len = 0;
	while (*s)
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


/*###############################################
#												#
#	MAIN FILE									#
#												#
###############################################*/

char	*get_line(t_file **o)
{
	char	*nxt;

	while (1)
	{
		(*o)->b_read = read((*o)->fd, (*o)->b, BUF_S);
		if ((*o)->b_read < 1)
			return (NULL);
		while ((*o)->i < BUF_S && (*o)->b[(*o)->i] && (*o)->b[(*o)->i] != '\n')
			(*o)->i++;
		if ((*o)->b[(*o)->i] == '\n' || (*o)->b[(*o)->i] == '\0')
		{
			nxt = (*o)->l;
			(*o)->l = ft_substr((*o)->b, 0, (*o)->i);
			if (!(*o)->l)
				return (NULL);
			nxt = ft_strjoin(nxt, (*o)->l);
			if (!nxt)
				return (NULL);
			free ((*o)->l);
			(*o)->l = ft_substr((*o)->b, (*o)->i, BUF_S - (*o)->i);
			if (!(*o)->l)
				return (NULL);
			break ;
		}
		else if ((*o)->i == BUF_S - 1)
		{
			(*o)->l = ft_strjoin((*o)->l, (*o)->b);	
			(*o)->i = 0;
		}
	}
	return (nxt);
}

int	o_cycle(t_file **o_p, t_file *o, int fd)
{
	if (!*o_p)
	{
		*o_p = o;
		(*o_p)->b = malloc (BUF_S);
		if (!(*o_p)->b)
			return (0);
		(*o_p)->fd = fd;
		(*o_p)->b_read = 0;
		(*o_p)->i = 0;
	}
	else
	{
		free((*o_p)->b);
		(*o_p)->b = NULL;
		free((*o_p)->l);
		(*o_p)->l = NULL;
	}
	return (1);
}

/*============INFO==============
|								| 
|  Definición del tipo s_file:  |
|...............................|
|								|
|	typedef struct	s_file		|
|	{							|
|		char	*b;				|
|		char	*line;			|
|		int		fd;				|
|		int		b_read;			|
|		int		i;				|
|	} t_file;					|
|								|
|===============================|
|								|
|	ALIAS DE BUFFER_SIZE		|
|...............................|
|								|
|	#define BUF_S BUFFER_SIZE	|
|								|
|______________________________*/

char	*get_next_line(int fd)
{
	static	t_file	o = {NULL, NULL, 0, 0, 0};
	static	t_file	*o_p = NULL;
	char	*line;

	if (!o_cycle(&o_p, &o, fd) || read(fd, o.b, 0) == -1 || BUF_S == 0)
		return (NULL);
	line = get_line(&o_p);
	if (!line)
		o_cycle(&o_p, &o, fd);
	return (line);
}