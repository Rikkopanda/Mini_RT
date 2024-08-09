/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_intersect.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:22:33 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 16:30:38 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f	intersect_plane(void *object, t_ray ray)
{
	const t_plane	*plane = (t_plane *)object;
	t_vec4f			result;
	float			t;
	float			d_dot_v;
	const float		epsilon = 1e-4f;

	d_dot_v = dot3(plane->vector, ray.direction);
	if (fabsf(d_dot_v) <= epsilon)
		return ((t_vec4f){0, 0, 0, -1});
	t = -(dot3(plane->vector, ray.origin) + \
		dot3(plane->location, -plane->vector)) / d_dot_v;
	if (t <= epsilon)
		return ((t_vec4f){0, 0, 0, -1});
	result = ray.origin + ray.direction * t;
	result[STATUS_INDEX] = PLANE;
	return (result);
}
