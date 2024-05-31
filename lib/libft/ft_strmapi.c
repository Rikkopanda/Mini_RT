/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 15:00:43 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 13:37:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}

// #include <stdio.h>

// static char	ft_upper(unsigned int i, char c)
// {
// 	if ((c >= 'a' && c <= 'z') && i >= 0)
// 		return (c - 32);
// 	return (c);
// }

// int	main(void)
// {
// 	printf("ft_strmapi %s\n", ft_strmapi("hello world", ft_upper));
// }
