/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 16:16:55 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/12 13:59:00 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start + len > s_len)
		len = s_len - start;
	if (len <= 0 || start > s_len)
		return (ft_strdup(""));
	sub = (char *)ft_calloc(len + 1, sizeof(char const));
	if (sub == NULL)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	return (sub);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char const		src[] = "test";
// 	unsigned int	start = 1;
// 	size_t			len = 2;

// 	printf("ft_substr %s\n", ft_substr(src, start, len));
// }
