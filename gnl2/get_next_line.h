/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:33:58 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/09 14:51:49 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

# define NL '\n'

char	*get_next_line(int fd);
char	*gnl_free(char *ptr);

char	*ft_strjoinfree(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int     ft_strlenc(const char *s, int c);
char    *ft_calloc(size_t nmemb, size_t size);

#endif
