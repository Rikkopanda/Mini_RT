/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:30:48 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/11 15:34:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	cmp;

	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	while (big[i] != 0 && i < len)
	{
		cmp = 0;
		while (big[cmp + i] == little[cmp] && (cmp + i) < len)
		{
			cmp++;
			if (little[cmp] == '\0')
				return (&((char *)big)[i]);
		}
		i++;
	}
	return (0);
}
