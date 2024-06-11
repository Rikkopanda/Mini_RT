#include "parser.h"

int	clamped_rgb_to_hex(int r, int g, int b)
{
	r = ft_max(ft_min(r, 255), 0);
	g = ft_max(ft_min(g, 255), 0);
	b = ft_max(ft_min(b, 255), 0);
	return ((r << 16) | (g << 8) | b);
}
