/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 12:50:48 by kwchu         #+#    #+#                 */
/*   Updated: 2023/11/27 16:30:24 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

void	*gnl_memcpy(void *dest, const void *src, size_t n);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strdup(const char *s);
ssize_t	gnl_strchr(const char *s, int c);
char	*get_next_line(int fd);
#endif
