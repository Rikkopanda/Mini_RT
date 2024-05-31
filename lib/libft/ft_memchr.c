/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:21:47 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/15 12:40:21 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((const char *)s)[i])
	{
		if (((unsigned char *)s)[i] == ((unsigned char)c))
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (0);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	src[] = "hallo";
// 	char	c = 'l';

// 	printf("memchr %s\n", (char *)memchr(src, c, 6));
// 	printf("ft_memchr %s\n", (char *)ft_memchr(src, c, 6));
// }
