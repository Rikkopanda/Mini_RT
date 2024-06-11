#include "../../include/minirt.h"


static int	digit_count(int num)
{
	int	count;

	count = 0;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

float	ft_atof(const char *s)
{
	int		sign;
	float	integer;
	float	decimal;
	int		digits;
	char	*dot_pos;

	dot_pos = 0;
	sign = 1;
	integer = (float)ft_atoi(s);
	if (integer < 0)
		sign = -1;
	dot_pos = ft_strchr(s, '.');
	if (!dot_pos)
		return (integer);
	decimal = (float)ft_atoi(dot_pos + 1);
	digits = digit_count(decimal);
	while (digits > 0)
	{
		decimal *= 0.1f;
		digits--;
	}
	return (integer + (decimal * sign));
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (0);
// 	printf("%f\n", ft_atof(argv[1]));
// 	return (0);
// }
