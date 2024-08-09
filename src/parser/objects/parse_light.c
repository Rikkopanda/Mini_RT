/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:52:45 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 16:56:11 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

static int	assign_geometric_properties(t_light *light, char **format)
{
	light->location = atovec3f(format[0]);
	light->diameter = ft_atof(format[1]);
	if (light->diameter <= 0)
	{
		fprintf(stderr, "Error: %.2f: light diameter \
cannot be 0 or lower.\n", light->diameter);
		return (0);
	}
	light->radius = light->diameter / 2;
	return (1);
}

static int	assign_light_properties(t_light *light, char **format)
{
	light->ratio = ft_atof(format[2]);
	if (light->ratio < 0.0f || light->ratio > 1.0f)
	{
		fprintf(stderr, "Error: %.2f: light brightness ratio \
out of range [0.0, 1.0]\n", light->ratio);
		return (0);
	}
	light->color.color_code = vec4rgb_to_int(atovec3f(format[3]));
	light->color.rgb_f = int_to_vec4rgb(light->color.color_code);
	light->color.rgb_f[STATUS_INDEX] = LIGHT;
	return (1);
}

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
	if (!assign_geometric_properties(light, format))
		return (free(light), 0);
	if (!assign_light_properties(light, format))
		return (free(light), 0);
	new = new_object(LIGHT, light);
	if (!new)
		return (perror("malloc error"), free(light), 0);
	append_object(objects, new);
	return (1);
}
