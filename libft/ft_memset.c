/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 13:55:20 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/15 17:53:04 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		((char *)s)[i] = c;
		i++;
		n--;
	}
	return (s);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str[] = "hallo";
// 	int		c = 'a';

// 	printf("memset %s\n", (char *)memset(str, c, sizeof(str)));
// 	printf("ft_memset %s\n", (char *)ft_memset(str, c, sizeof(str)));
// }
