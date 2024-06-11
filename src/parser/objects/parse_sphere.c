#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int	parse_sphere(t_object **head, char **format)
{
	t_sphere	*sphere;
	t_object	*new;

	if (ft_2darray_size(format) != 3)
	{
		fprintf(stderr, "Error: incorrect sphere info format.\n");
		return (0);
	}
	sphere = malloc(sizeof(*sphere));
	if (!sphere)
		return (perror("malloc error"), 0);
	sphere->location = atovec3f(format[0]);
	sphere->diameter = ft_atof(format[1]);
	if (sphere->diameter <= 0)
	{
		fprintf(stderr, "Error: %.2f: sphere diameter \
cannot be 0 or lower.\n", sphere->diameter);
		return (free(sphere), 0);
	}
	sphere->radius /= sphere->diameter;
	sphere->hexcolor = ft_atohex(format[2]);
	new = new_object(SPHERE, sphere);
	if (!new)
		return (perror("malloc error"), free(sphere), 0);
	append_object(head, new);
	return (1);
}
