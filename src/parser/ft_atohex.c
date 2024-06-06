#include "parser.h"
#include "libft.h"

int	ft_atohex(const char *a_rgb)
{
	char	**split;
	int		rgb[3];

	split = ft_split(a_rgb, ',');
	if (!split)
		return (perror("malloc error"), 0);
	if (ft_2darray_size(split) != 3)
		return (ft_free_2darray(split), 0);
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	ft_free_2darray(split);
	return (clamped_rgb_to_hex(rgb[0], rgb[1], rgb[2]));
}
