/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:32:11 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/12 18:21:43 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# ifndef K_NL
#  define K_NL '\n'
# endif

# ifndef K_ES
#  define K_ES 0
# endif

char	*get_next_line(int fd);
char	*free_null(char *buf);
int		ft_strlenc(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_and_free(char *s1, const char *s2);

#endif
