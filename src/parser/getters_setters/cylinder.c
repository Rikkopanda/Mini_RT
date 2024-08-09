/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 15:14:15 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 15:18:02 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f	get_location_cylinder(void *object)
{
	const t_cylinder	*cylinder = (t_cylinder *)object;

	return (cylinder->location);
}

void	set_location_cylinder(void *object, int xyz_index, int addition)
{
	const t_cylinder	*cylinder = (t_cylinder *)object;

	cylinder->location[xyz_index] += addition;
}

t_vec4f	get_color_cylinder(void *object)
{
	const t_cylinder	*cylinder = (t_cylinder *)object;

	return (cylinder->color.rgb_f);
}

float	get_smoothness_cylinder(void *object)
{
	const t_cylinder	*cylinder = (t_cylinder *)object;

	return (cylinder->smoothness);
}

t_vec4f	get_normal_cylinder(void *object, t_vec4f point)
{
	const t_cylinder	*cylinder = (t_cylinder *)object;
	const t_vec4f		top_center = cylinder->location + \
									cylinder->vector * (cylinder->height / 2);
	const t_vec4f		bottom_center = cylinder->location - \
									cylinder->vector * (cylinder->height / 2);
	t_vec4f				perpendicular_point;
	const float			epsilon = 1e-4f;

	if (fabsf(dot3(point - top_center, cylinder->vector)) < epsilon)
		return (cylinder->vector);
	if (fabsf(dot3(point - bottom_center, cylinder->vector)) < epsilon)
		return (-cylinder->vector);
	perpendicular_point = cylinder->location + cylinder->vector * \
				dot3(point - cylinder->location, cylinder->vector);
	point -= perpendicular_point;
	return (normalize_vector(&point));
}
