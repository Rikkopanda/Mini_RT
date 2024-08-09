/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:52:36 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:12:47 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

static int	has_valid_ranges(t_cylinder *cylinder)
{
	if (!ft_vec_in_range(cylinder->vector, -1, 1))
	{
		fprintf(stderr, "Error: cylinder normal vector out of range [-1, 1]\n");
		return (0);
	}
	if (cylinder->diameter <= 0)
	{
		fprintf(stderr, "Error: %.2f: cylinder diameter \
cannot be 0 or lower.\n", cylinder->diameter);
		return (0);
	}
	if (cylinder->height <= 0)
	{
		fprintf(stderr, "Error: %.2f: cylinder height \
cannot be 0 or lower.\n", cylinder->height);
		return (0);
	}
	return (1);
}

static int	assign_geometric_properties(t_cylinder *cylinder, char **format)
{
	cylinder->location = atovec3f(format[0]);
	cylinder->vector = atovec3f(format[1]);
	cylinder->diameter = ft_atof(format[2]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atof(format[3]);
	if (!has_valid_ranges(cylinder))
		return (0);
	normalize_vector(&cylinder->vector);
	return (1);
}

static int	assign_material_properties(t_cylinder *cylinder, char **format)
{
	cylinder->color.color_code = ft_rgb_to_int(format[4]);
	cylinder->color.rgb_f = int_to_vec4rgb(cylinder->color.color_code);
	cylinder->color.rgb_f[STATUS_INDEX] = CYLINDER;
	cylinder->smoothness = ft_atof(format[5]);
	if (cylinder->smoothness < 0 || cylinder->smoothness > 1.0f)
	{
		fprintf(stderr, "Error: cylinder smoothness out of range [0, 1]\n");
		return (0);
	}
	return (1);
}

int	parse_cylinder(t_object **objects, char **format)
{
	t_cylinder	*cylinder;
	t_object	*new;

	if (ft_2darray_size(format) != 6)
	{
		fprintf(stderr, "Error: incorrect cylinder info format.\n");
		return (0);
	}
	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
		return (perror("malloc error"), 0);
	if (!assign_geometric_properties(cylinder, format))
		return (free(cylinder), 0);
	if (!assign_material_properties(cylinder, format))
		return (free(cylinder), 0);
	new = new_object(CYLINDER, cylinder);
	if (!new)
		return (perror("malloc error"), free(cylinder), 0);
	append_object(objects, new);
	return (1);
}
