/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 18:00:00 by kwchu         #+#    #+#                 */
/*   Updated: 2024/02/16 20:05:44 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	begin;
	int	end;

	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] != 0)
	{
		if (!ft_ischarset(s1[begin], set))
			break ;
		begin++;
	}
	while (end > 0)
	{
		if (!ft_ischarset(s1[end - 1], set))
			break ;
		end--;
	}
	if (end < begin)
		return (ft_substr(s1, begin, begin - end));
	return (ft_substr(s1, begin, end - begin));
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char const	src[] = "hello world";

// 	printf("ft_strtrim: %s\n", ft_strtrim(src, "hewl"));
// }
