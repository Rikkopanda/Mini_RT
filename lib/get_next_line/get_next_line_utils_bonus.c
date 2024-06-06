/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 12:50:42 by kwchu         #+#    #+#                 */
/*   Updated: 2023/11/27 16:30:24 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = 0;
	while (s[s_len] != 0)
		s_len++;
	if (start + len > s_len)
		len = s_len - start;
	if (len <= 0 || start > s_len)
	{
		sub = (char *)malloc(1 * sizeof(char));
		len = 0;
	}
	else
		sub = (char *)malloc(len + 1 * sizeof(char const));
	if (sub == NULL)
		return (NULL);
	sub[len] = 0;
	gnl_memcpy(sub, s + start, len);
	return (sub);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		size;
	char	*dst;

	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len] != 0)
		s1_len++;
	while (s2[s2_len] != 0)
		s2_len++;
	size = s1_len + s2_len;
	dst = (char *)malloc(size + 1 * sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst[size] = 0;
	gnl_memcpy(dst, s1, s1_len);
	gnl_memcpy(dst + s1_len, s2, s2_len);
	return (dst);
}

char	*gnl_strdup(const char *s)
{
	int		s_len;
	char	*dup;

	s_len = 0;
	while (s[s_len] != 0)
		s_len++;
	dup = (char *)malloc(s_len + 1 * sizeof(char));
	if (dup == NULL)
		return (NULL);
	dup[s_len] = 0;
	gnl_memcpy(dup, s, s_len);
	return (dup);
}

ssize_t	gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return (1);
	return (0);
}
