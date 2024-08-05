#include <stdio.h>
#include "parser.h"

int	parse_plane(t_object **objects, char **format)
{
	t_plane		*plane;
	t_object	*new;

	if (ft_2darray_size(format) != 3)
	{
		fprintf(stderr, "Error: incorrect plane info format.\n");
		return (0);
	}
	plane = malloc(sizeof(*plane));
	if (!plane)
		return (perror("malloc error"), 0);
	plane->location = atovec3f(format[0]);
	plane->vector = atovec3f(format[1]);
	if (!ft_vec_in_range(plane->vector, -1, 1))
	{
		fprintf(stderr, "Error: plane normal vector out of range [-1, 1]\n");
		return (free(plane), 0);
	}
	normalize_vector(&plane->vector);
	plane->color.color_code = ft_atohex(format[2]);
	plane->color.rgb_f = int_to_vec4rgb(plane->color.color_code);
	new = new_object(PLANE, plane);
	if (!new)
		return (perror("malloc error"), free(plane), 0);
	append_object(objects, new);
	return (1);
}
