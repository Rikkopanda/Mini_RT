/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:31:12 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/19 16:17:51 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] != 0 && dst_len + i + 1 < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// #include <bsd/string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	src[6] = "hallo";
// 	char	src2[6] = "hallo";
// 	char	dst[6] = "00000";
// 	char	dst2[6] = "00000";

// 	printf("strlcat %zu\n", strlcat(dst, src, sizeof(dst)));
// 	printf("ft_strlcat %zu\n", ft_strlcat(dst2, src2, sizeof(dst2)));
// }
