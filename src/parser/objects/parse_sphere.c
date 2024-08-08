#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

static int assign_geometric_properties(t_sphere *sphere, char **format)
{
	sphere->location = atovec3f(format[0]);
	sphere->diameter = ft_atof(format[1]);
	if (sphere->diameter <= 0)
	{
		fprintf(stderr, "Error: %.2f: sphere diameter \
cannot be 0 or lower.\n", sphere->diameter);
		return (0);
	}
	sphere->radius = sphere->diameter / 2;
	return (1);
}

static int assign_color_properties(t_sphere *sphere, char **format)
{
	
}

int	parse_sphere(t_object **head, char **format)
{
	t_sphere	*sphere;
	t_object	*new;

	if (ft_2darray_size(format) != 4)
	{
		fprintf(stderr, "Error: incorrect sphere info format.\n");
		return (0);
	}
	sphere = malloc(sizeof(*sphere));
	if (!sphere)
		return (perror("malloc error"), 0);
	if (!assign_geometric_properties(sphere, format))
		return (free(sphere), 0);
	sphere->color.color_code = ft_atohex(format[2]);
	sphere->color.rgb_f = int_to_vec4rgb(sphere->color.color_code);
	sphere->color.rgb_f[STATUS_INDEX] = SPHERE;
	sphere->smoothness = ft_atof(format[3]);
	new = new_object(SPHERE, sphere);
	if (!new)
		return (perror("malloc error"), free(sphere), 0);
	append_object(head, new);
	return (1);
}
