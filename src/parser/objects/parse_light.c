#include <stdio.h>
#include "parser.h"

int	parse_light(t_object **objects, char **format)
{
	t_light		*light;
	t_object	*new;

	if (ft_2darray_size(format) != 4)
	{
		fprintf(stderr, "Error: incorrect light info format.\n");
		return (0);
	}
	light = malloc(sizeof(*light));
	if (!light)
		return (perror("malloc error"), 0);
	light->location = atovec3f(format[0]);
	light->diameter = ft_atof(format[1]);
	light->radius = light->diameter / 2;
	light->ratio = ft_atof(format[2]);
	if (light->ratio < 0.0f || light->ratio > 1.0f)
	{
		fprintf(stderr, "Error: %.2f: light brightness ratio \
out of range [0.0, 1.0]\n", light->ratio);
		return (free(light), 0);
	}
	light->color.color_code = vec4rgb_to_int(atovec3f(format[3]));
	light->color.rgb_f = int_to_vec4rgb(light->color.color_code);
	light->color.rgb_f[STATUS_INDEX] = LIGHT;
	new = new_object(LIGHT, light);
	if (!new)
		return (perror("malloc error"), free(light), 0);
	append_object(objects, new);
	return (1);
}
