/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 14:04:50 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/10 14:40:57 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	positive;
	int	n_len;

	positive = 1;
	n_len = 0;
	if (n == 0)
		n_len++;
	if (n < 0)
	{
		positive = 0;
		n /= 10;
		n = -n;
		n_len += 2;
	}
	while (n > 0)
	{
		n /= 10;
		n_len++;
	}
	if (positive == 0)
		return (-n_len);
	return (n_len);
}

static void	ft_splitnbr(int nb, char *str, int n_len)
{
	int	digit;
	int	remainder;

	digit = nb % 10;
	remainder = nb / 10;
	if (n_len > 0)
		n_len--;
	if (nb < 0)
	{
		digit = -digit;
		remainder = -remainder;
	}
	if (remainder > 0)
		ft_splitnbr(remainder, str, n_len);
	str[n_len] = (digit + '0');
}

char	*ft_itoa(int n)
{
	int		n_len;
	int		positive;
	char	*str;

	n_len = ft_nbrlen(n);
	positive = 1;
	if (n_len <= 0)
	{
		positive = 0;
		n_len = -n_len;
	}
	str = (char *)ft_calloc(n_len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_splitnbr(n, str, n_len);
	if (positive == 0)
		str[0] = '-';
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(__INT_MAX__));
// }
