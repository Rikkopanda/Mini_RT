#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int	parse_sphere(t_object **head, char **format)
{
	t_sphere	*sphere;
	t_object	*new;

	// fprintf(stderr, "parsing sphere\n");
	if (ft_2darray_size(format) != 3)
		return (0);
	sphere = malloc(sizeof(*sphere));
	if (!sphere)
		return (perror("malloc error"), 0);
	sphere->location = atovec3f(format[0]);
	sphere->diameter = ft_atof(format[1]);
	sphere->hexcolor = ft_atohex(format[2]);
	new = new_object(SPHERE, sphere);
	if (!new)
		return (perror("malloc error"), free(sphere), 0);
	append_object(head, new);
	return (1);
}
