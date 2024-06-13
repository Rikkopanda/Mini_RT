#include "parser.h"

static void	swap_floats(float *a, float *b)
{
	float	tmp;

	if (a != b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

int	ft_vec_in_range(t_vec4f vec4f, float low, float high)
{
	if (high < low)
		swap_floats(&high, &low);
	if (vec4f[0] < low || vec4f[0] > high)
		return (0);
	if (vec4f[1] < low || vec4f[1] > high)
		return (0);
	if (vec4f[2] < low || vec4f[2] > high)
		return (0);
	if (vec4f[3] < low || vec4f[3] > high)
		return (0);
	return (1);
}
