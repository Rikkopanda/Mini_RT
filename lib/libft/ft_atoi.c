/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:55:08 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/09 13:04:25 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	ft_nbrsplit(const char *nptr, int i)
{
	int	fnum;

	fnum = 0;
	while (ft_isdigit(nptr[i]))
	{
		fnum *= 10;
		fnum += (nptr[i] - '0');
		i++;
	}
	return (fnum);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	positive;

	i = 0;
	positive = 1;
	while (nptr[i] != 0 && ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			positive = -positive;
		i++;
	}
	if (ft_isdigit(nptr[i]))
		return (ft_nbrsplit(nptr, i) * positive);
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("max int = %d\n", ft_atoi("2147483647"));
// 	printf("max int + 1 = %d\n", ft_atoi("2147483648"));
// 	printf("min int = %d\n", ft_atoi("-2147483648"));
// 	printf("space test at start = %d\n", ft_atoi("    -214743648"));
// 	printf("space test inbetween = %d\n", ft_atoi("-2147 48 3648 "));
// 	printf("all spaces test = %d\n", ft_atoi("\v\f\t\n\r 3648"));
// 	printf("asfhjafkh = %d\n", ft_atoi("asfhjafkh"));
// }
