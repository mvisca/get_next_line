#include "get_next_line.h"

static char	*gnl_free_null(char **b, char **l)
{
	free(*b);
	*b = NULL;
	free(*l);
	*l = NULL;
	return (NULL);
}

static char	*gnl_read(int fd, char **raw)
{
	char	*buf;
	char	*tmp;
	int		b_read;
	printf ("read\n");
	
	buf = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (gnl_free_null(raw, raw));
	
	while (1)
	{

	printf ("read -- loop\n");

		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
			return (gnl_free_null(&buf, raw));
		buf[b_read] = 0;

		printf ("read -- buf : %s\n", buf);

		tmp = *raw;
		*raw = ft_strjoin(tmp, buf);
		if (!*raw)
			return (gnl_free_null(&buf, &tmp));
		if (ft_strchr(*raw, NL) && !gnl_free_null(&buf, &tmp))
			break ;
		free(tmp);
	}
	printf ("read -- raw : %s", *raw);
	return (*raw);	
}

static char	*gnl_get(char *raw, char **line)
{
	int		line_break;

	printf ("get\n");
	printf ("get -- raw : %s\n", raw);

	line_break = 0;
	while(raw[line_break] && raw[line_break] != NL)
		line_break++;
	if (ft_strchr(raw, NL))
	{
		*line = ft_substr(raw, 0, line_break);
		if (!*line)
			return (gnl_free_null(&raw, &raw));
		printf ("get -- line : %s", *line);
	}
	return (*line);
}

static char	*gnl_clean(char **raw)
{
	int		next_line_len;
	int		extra_line_len;
	char	*new_raw;

	printf ("clean\n");
	next_line_len = 0;
	extra_line_len = 0;
	while ((*raw)[next_line_len] && (*raw)[next_line_len] != NL)
		next_line_len++;
	while ((*raw)[next_line_len + extra_line_len + 1]) 
		extra_line_len++;
	new_raw = ft_substr(*raw, next_line_len + 1, extra_line_len);
	free(*raw);
	*raw = new_raw;
	return (*raw);
}

char    *get_next_line(int fd)
{
	static char	*raw = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	printf ("gnl\n");
	if (gnl_read(fd, &raw) && gnl_get(raw, &line) && gnl_clean(&raw))
		return (line);
	else if (raw)
		return (raw);
	return (NULL);
}
