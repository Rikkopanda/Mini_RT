#include <stdio.h>
#include "parser.h"

int	parse_cylinder(t_object **objects, char **format)
{
	t_cylinder	*cylinder;
	t_object	*new;

	// fprintf(stderr, "parsing cylinder\n");
	if (ft_2darray_size(format) != 5)
		return (0);
	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
		return (perror("malloc error"), 0);
	cylinder->location = atovec3f(format[0]);
	cylinder->vector = atovec3f(format[1]);
	if (cylinder->vector[0] < -1 || cylinder->vector[0] > 1 ||
		cylinder->vector[1] < -1 || cylinder->vector[1] > 1 ||
		cylinder->vector[2] < -1 || cylinder->vector[2] > 1)
	{
		fprintf(stderr, "Error: cylinder normal vector out of range [-1, 1]\n");
		return (free(cylinder), 0);
	}
	cylinder->diameter = ft_atof(format[2]);
	cylinder->height = ft_atof(format[3]);
	cylinder->hexcolor = ft_atohex(format[4]);
	new = new_object(CYLINDER, cylinder);
	if (!new)
		return (perror("malloc error"), free(cylinder), 0);
	append_object(objects, new);
	return (1);
}
