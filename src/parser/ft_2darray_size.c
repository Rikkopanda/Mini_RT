#include "../../include/minirt.h"

size_t	ft_2darray_size(char **arr)
{
	size_t	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}
