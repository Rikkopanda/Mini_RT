/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:21:40 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/15 17:47:20 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
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

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	src[] = "hallo";
//	char	src2[] = "hallo";
// 	char	dst[] = "00000";
//	char	dst2[] = "00000";

// 	printf("memcpy %s\n", (char *)memcpy(dst, src, 3));
// 	printf("ft_memcpy %s\n", (char *)ft_memcpy(dst2, src2, 3));
// }
