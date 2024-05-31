/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:24:20 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/09 15:15:23 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	return (0);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	src[] = "hallo";
// 	char	c = 'l';

// 	printf("strchr %s\n", strchr(src, c));
// 	printf("ft_strchr %s\n", ft_strchr(src, c));
// }
