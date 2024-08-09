/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_intersect.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:24:41 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 16:24:49 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f	intersect_light(void *object, t_ray ray)
{
	const t_light		*light = (t_light *)object;
	const t_vec4f		ray_to_object = light->location - ray.origin;
	t_sphere_intersect	intersect;
	float				t1;
	t_vec4f				result;

	intersect.perpendicular_point = dot3(ray_to_object, ray.direction);
	if (intersect.perpendicular_point < 0.0f)
		return ((t_vec4f){0, 0, 0, -1});
	intersect.pp_distance = dot3(ray_to_object, ray_to_object) \
							- powf(intersect.perpendicular_point, 2);
	intersect.radius_squared = light->radius * light->radius;
	if (intersect.pp_distance > intersect.radius_squared)
		return ((t_vec4f){0, 0, 0, -1});
	t1 = sqrtf(intersect.radius_squared - intersect.pp_distance);
	result = ray.origin + ray.direction * (intersect.perpendicular_point - t1);
	result[STATUS_INDEX] = LIGHT;
	return (result);
}
