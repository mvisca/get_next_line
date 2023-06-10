/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:33:58 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/10 20:55:06 by mvisca           ###   ########.fr       */
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
# define K_ES '\0'

char	*get_next_line(int fd);

char	*ft_strjoinfree(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int     ft_strlenc(const char *s, int c);
void    *ft_calloc(size_t n, size_t s);

#endif
