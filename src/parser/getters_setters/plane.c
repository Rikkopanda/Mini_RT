/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 15:25:18 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 15:26:48 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f get_location_plane(void *object)
{
	const t_plane	*plane = (t_plane *)object;

	return (plane->location);
}

void	set_location_plane(void *object, int xyz_index, int addition)
{
	const t_plane	*plane = (t_plane *)object;

	plane->location[xyz_index] += addition;
}

t_vec4f get_color_plane(void *object)
{
	const t_plane	*plane = (t_plane *)object;

	return (plane->color.rgb_f);
}

float	get_smoothness_plane(void *object)
{
	const t_plane	*plane = (t_plane *)object;

	return (plane->smoothness);
}

t_vec4f get_normal_plane(void *object, t_vec4f point)
{
	const t_plane	*plane = (t_plane *)object;

	return (plane->vector);
}
