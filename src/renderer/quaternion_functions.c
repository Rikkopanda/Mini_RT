/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:02:58 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/08 14:23:10 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f	invert_quaternion(t_vec4f quaternion)
{
	const float	squared = quaternion[0] * quaternion[0] + \
							quaternion[1] * quaternion[1] + \
							quaternion[2] * quaternion[2] + \
							quaternion[3] * quaternion[3];
	float		inverse;

	if (squared == 0.0f)
		return (quaternion);
	inverse = 1.0f / squared;
	return ((t_vec4f){
		quaternion[0] * inverse, \
		-quaternion[1] * inverse, \
		-quaternion[2] * inverse, \
		-quaternion[3] * inverse
	});
}

t_vec4f	invert_unit_quaternion(t_vec4f uq)
{
	return ((t_vec4f){uq[0], -uq[1], -uq[2], -uq[3]});
}

t_vec4f	axis_angle_to_quaternion(t_vec4f axis, float angle_rad)
{
	if (angle_rad == 0.0f)
		return ((t_vec4f){1, 0, 0, 0});
	return ((t_vec4f){
		cosf(angle_rad / 2), \
		axis[0] * sinf(angle_rad / 2),
		axis[1] * sinf(angle_rad / 2),
		axis[2] * sinf(angle_rad / 2)
	});
}

/**
 * @note multiplying quaternions according to Hamilton's product
 * Source: https://en.wikipedia.org/wiki/Quaternion#Hamilton_product
 * Source: https://www.meccanismocomplesso.org/en/hamiltons-quaternions-and-3d-rotation-with-python/
 */
t_vec4f	hamilton_product(t_vec4f q1, t_vec4f q2)
{
	t_vec4f	product;

	product[0] = q1[0] * q2[0] - \
				q1[1] * q2[1] - \
				q1[2] * q2[2] - \
				q1[3] * q2[3];
	product[1] = q1[0] * q2[1] + \
				q1[1] * q2[0] + \
				q1[2] * q2[3] - \
				q1[3] * q2[2];
	product[2] = q1[0] * q2[2] + \
				q1[2] * q2[0] + \
				q1[3] * q2[1] - \
				q1[1] * q2[3];
	product[3] = q1[0] * q2[3] + \
				q1[3] * q2[0] + \
				q1[1] * q2[2] - \
				q1[2] * q2[1];
	return (product);
}
