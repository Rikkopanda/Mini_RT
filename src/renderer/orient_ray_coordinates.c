/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orient_ray_coordinates.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 14:01:59 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/08/14 16:48:40 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int is_zero_vector3(t_vec4f a)
{
	return (a[0] == 0 && a[1] == 0 && a[2] == 0);
}

static t_vec4f	orthogonal_vector(t_vec4f v)
{
	t_vec4f	non_collinear;

	non_collinear = (t_vec4f){1, 0, 0, 1};
	if (fabsf(v[0]) > fabsf(v[2]))
		non_collinear = (t_vec4f){0, 0, 1, 1};
	return (cross3(v, non_collinear));
}

t_vec4f	orientation_to_quaternion_rotation(t_vec4f orientation)
{
	const t_vec4f	default_orientation = {0, 0, -1, 1};
	t_vec4f			cross_product;
	t_vec4f			quaternion;
	t_vec4f			orthogonal;
	float			dot_product;

	if (is_zero_vector3(orientation))
		return ((t_vec4f){0, 1, 0, 0});
	normalize_vector(&orientation);
	cross_product = cross3(default_orientation, orientation);
	dot_product = dot3(default_orientation, orientation);
	if (dot_product < -0.99999f)
	{
		orthogonal = orthogonal_vector(orientation);
		return ((t_vec4f){0, orthogonal[0], orthogonal[1], orthogonal[2]});
	}
	quaternion[0] = 1 + dot_product;
	quaternion[1] = cross_product[0];
	quaternion[2] = cross_product[1];
	quaternion[3] = cross_product[2];
	return (normalize_quaternion(&quaternion));
}

/**
 * @note converts a point to a pure quaternion and applies rotation using the 
 * formula: P' = qpq*
 * P' = rotated point
 * q = the rotation quaternion (q_rotate)
 * q* = inverse of the rotation quaternion (q_inverse)
 * Source: https://danceswithcode.net/
 * engineeringnotes/quaternions/quaternions.html
 * Source: https://www.youtube.com/watch?v=3BR8tK-LuB0
 */
t_vec4f	apply_rotation(t_vec4f point, t_vec4f q_rotation)
{
	const t_vec4f	quaternion_point = {0, point[0], point[1], point[2]};
	const t_vec4f	q_inverse = invert_unit_quaternion(q_rotation);
	const t_vec4f	rotated_point = hamilton_product(\
						hamilton_product(q_rotation, \
						quaternion_point), q_inverse);

	return ((t_vec4f){rotated_point[1], rotated_point[2], rotated_point[3], 1});
}
