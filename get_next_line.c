#include "get_next_line.h"

static char	*gnl_free_null(char **b, char **l)
{
	printf ("FREENULL\n");
	if (b && *b)
		free(*b);
	*b = NULL;
	if (l && *l)
		free(*l);
	*l = NULL;
	return (NULL);
}

static char	*gnl_read(int fd, char **raw)
{
	char	*buf;
	char	*tmp;
	int		b_read;

	printf ("READ\n");
	buf = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (gnl_free_null(raw, raw));
	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
			return (gnl_free_null(&buf, raw));
		if (b_read == 0)
			return (gnl_free_null(&buf, &buf));
		buf[b_read] = 0;
		tmp = (*raw);
		(*raw) = ft_strjoin(tmp, buf);
		if (!(*raw))
			return (gnl_free_null(&buf, &tmp));
		if (ft_strchr((*raw), NL) && !gnl_free_null(&buf, &tmp))
			break ;
		gnl_free_null(&tmp, &tmp);
	}
	printf ("READ -- RAW : %s\n", *raw);
	return (*raw);	
}

static char	*gnl_get(char *raw, char **line)
{
	printf ("GET\n");

	int		line_break;

	line_break = 0;
	while(raw[line_break] && raw[line_break] != NL)
		line_break++;
	if (ft_strchr(raw, NL))
	{
		*line = ft_substr(raw, 0, line_break);
		if (!*line)
			return (gnl_free_null(&raw, &raw));
	}
	return (*line);
}

static char	*gnl_clean(char **raw)
{
	printf ("CLEAN\n");

	int		next_line_len;
	int		extra_line_len;
	char	*new_raw;

	next_line_len = 0;
	extra_line_len = 0;
	while ((*raw)[next_line_len] && (*raw)[next_line_len] != NL)
		next_line_len++;
	while ((*raw)[next_line_len + extra_line_len + 1]) 
		extra_line_len++;
	new_raw = ft_substr(*raw, next_line_len + 1, extra_line_len);
	gnl_free_null(raw, raw);
	*raw = new_raw;
	printf ("CLEAN : %s\n", *raw);
	return (*raw);
}

char    *get_next_line(int fd)
{
	printf ("GNL\n");

	static char	*raw = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);

	if (gnl_read(fd, &raw) && gnl_get(raw, &line) && gnl_clean(&raw))
	{
		return (line);
	}
	else if (raw)
	{
		line = ft_strdup(raw);
		//free(raw);
		return (line);
	}
	return (NULL);
}
