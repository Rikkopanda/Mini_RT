#include <stdio.h>
#include "parser.h"

int	parse_light(t_object **objects, char **format)
{
	t_light		*light;
	t_object	*new;

	if (ft_2darray_size(format) != 3)
	{
		fprintf(stderr, "Error: incorrect light info format.\n");
		return (0);
	}
	light = malloc(sizeof(*light));
	if (!light)
		return (perror("malloc error"), 0);
	light->location = atovec3f(format[0]);
	light->ratio = ft_atof(format[1]);
	if (light->ratio < 0.0f || light->ratio > 1.0f)
	{
		fprintf(stderr, "Error: %.2f: light brightness ratio \
out of range [0.0, 1.0]\n", light->ratio);
		return (free(light), 0);
	}
	light->color.color_code = 0xFFFFFF;
	light->color.rgb_f = int_to_vec4rgb(light->color.color_code);
	new = new_object(LIGHT, light);
	if (!new)
		return (perror("malloc error"), free(light), 0);
	append_object(objects, new);
	return (1);
}
