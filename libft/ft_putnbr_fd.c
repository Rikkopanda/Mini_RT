/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 12:43:14 by kwchu         #+#    #+#                 */
/*   Updated: 2023/10/07 15:00:19 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	digit;
	int	remainder;

	digit = n % 10;
	remainder = n / 10;
	if (n < 0)
	{
		ft_putchar('-', fd);
		digit = -digit;
		remainder = -remainder;
	}
	if (remainder > 0)
		ft_putnbr_fd(remainder, fd);
	ft_putchar(digit + '0', fd);
}

// #include <stdio.h>

// int	main(void)
// {
// 	ft_putnbr_fd(-2147483648, 1);
// 	printf("\n");
// 	ft_putnbr_fd(2147483647, 1);
// 	printf("\n");
// 	ft_putnbr_fd(0, 1);
// 	printf("\n");
// 	ft_putnbr_fd(1, 1);
// }
