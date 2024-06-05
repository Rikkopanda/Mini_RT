#include <stdio.h>
#include "parser.h"

int	parse_plane(t_object **objects, char **format)
{
	t_plane		*plane;
	t_object	*new;

	// fprintf(stderr, "parsing plane\n");
	if (ft_2darray_size(format) != 3)
		return (0);
	plane = malloc(sizeof(*plane));
	if (!plane)
		return (perror("malloc error"), 0);
	plane->location = atovec3f(format[0]);
	plane->vector = atovec3f(format[1]);
	if (plane->vector[0] < -1 || plane->vector[0] > 1 ||
		plane->vector[1] < -1 || plane->vector[1] > 1 ||
		plane->vector[2] < -1 || plane->vector[2] > 1)
	{
		fprintf(stderr, "Error: plane normal vector out of range [-1, 1]\n");
		return (free(plane), 0);
	}
	plane->hexcolor = ft_atohex(format[2]);
	new = new_object(PLANE, plane);
	if (!new)
		return (perror("malloc error"), free(plane), 0);
	append_object(objects, new);
	return (1);
}
