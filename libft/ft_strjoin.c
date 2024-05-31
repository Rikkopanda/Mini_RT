/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 16:56:06 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 13:36:58 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		offset;
	int		size;
	char	*dst;

	offset = ft_strlen(s1);
	size = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)ft_calloc(size + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s1, offset);
	ft_memcpy(dst + offset, s2, ft_strlen(s2));
	return (dst);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	src[] = " world";
// 	char	dst[] = "hello";

// 	printf("ft_strjoin %s\n", ft_strjoin(dst, src));
// }
