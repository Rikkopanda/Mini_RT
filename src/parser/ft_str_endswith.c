/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_endswith.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:11:13 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:11:14 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_str_endswith(const char *s, const char *end)
{
	int	len;
	int	i;

	if (!s || !end)
		return (NULL);
	if (s == end)
		return ((char *)s);
	len = ft_strlen(end) - 1;
	i = ft_strlen(s) - 1;
	if (len < 0 || i < 0 || i < len)
		return (NULL);
	while (len >= 0)
	{
		if (end[len] != s[i])
			return (NULL);
		len--;
		i--;
	}
	return ((char *)(s + i + 1));
}
