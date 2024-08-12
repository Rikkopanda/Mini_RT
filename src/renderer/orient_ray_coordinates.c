/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orient_ray_coordinates.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 14:01:59 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/08/12 20:34:19 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
