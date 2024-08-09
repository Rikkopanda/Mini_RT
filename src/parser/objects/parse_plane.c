/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:49:01 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:05:50 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

static int	assign_geometric_properties(t_plane *plane, char **format)
{
	plane->location = atovec3f(format[0]);
	plane->vector = atovec3f(format[1]);
	if (!ft_vec_in_range(plane->vector, -1, 1))
	{
		fprintf(stderr, "Error: plane normal vector out of range [-1, 1]\n");
		return (0);
	}
	normalize_vector(&plane->vector);
	return (1);
}

static int	assign_material_properties(t_plane *plane, char **format)
{
	plane->color.color_code = ft_rgb_to_int(format[2]);
	plane->color.rgb_f = int_to_vec4rgb(plane->color.color_code);
	plane->color.rgb_f[STATUS_INDEX] = PLANE;
	plane->smoothness = ft_atof(format[3]);
	if (plane->smoothness < 0 || plane->smoothness > 1.0f)
	{
		fprintf(stderr, "Error: plane smoothness out of range [0, 1]\n");
		return (0);
	}
	return (1);
}

int	parse_plane(t_object **objects, char **format)
{
	t_plane		*plane;
	t_object	*new;

	if (ft_2darray_size(format) != 4)
	{
		fprintf(stderr, "Error: incorrect plane info format.\n");
		return (0);
	}
	plane = malloc(sizeof(*plane));
	if (!plane)
		return (perror("malloc error"), 0);
	if (!assign_geometric_properties(plane, format))
		return (free(plane), 0);
	if (!assign_material_properties(plane, format))
		return (free(plane), 0);
	new = new_object(PLANE, plane);
	if (!new)
		return (perror("malloc error"), free(plane), 0);
	append_object(objects, new);
	return (1);
}
