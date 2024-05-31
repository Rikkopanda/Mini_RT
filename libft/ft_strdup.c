/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:00:44 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 13:36:55 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	void	*dup;

	dup = (void *) ft_calloc(ft_strlen(s) + 1, sizeof(const char));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, (const void *)s, ft_strlen(s));
	return ((char *)dup);
}
