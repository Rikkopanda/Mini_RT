/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_intersect.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:25:22 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 16:31:42 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calculate_discriminant(t_ray ray, const t_cylinder *cylinder, \
										t_cylinder_intersect *intersect)
{
	const t_vec4f	x = ray.origin - cylinder->location;
	const float		d_dot_v = dot3(ray.direction, cylinder->vector);
	const float		x_dot_v = dot3(x, cylinder->vector);
	float			c;

	intersect->a = dot3(ray.direction, ray.direction) - powf(d_dot_v, 2);
	intersect->b = 2 * (dot3(ray.direction, x) - d_dot_v * x_dot_v);
	c = dot3(x, x) - powf(x_dot_v, 2) - powf(cylinder->radius, 2);
	intersect->d_dot_v = d_dot_v;
	return (powf(intersect->b, 2) - 4 * intersect->a * c);
}

static void	validate_intersect_distance(t_ray ray, const t_cylinder *cylinder,
										t_cylinder_intersect *intersect)
{
	float			height1;
	float			height2;
	const float		half_height = cylinder->height / 2;
	const t_vec4f	point[4] = {
		ray.origin + ray.direction * intersect->t1,
		ray.origin + ray.direction * intersect->t2,
		ray.origin + ray.direction * intersect->t_top,
		ray.origin + ray.direction * intersect->t_bottom,
	};

	height1 = dot3(point[0] - cylinder->location, cylinder->vector) \
				/ vector_length(cylinder->vector);
	height2 = dot3(point[1] - cylinder->location, cylinder->vector) \
				/ vector_length(cylinder->vector);
	if (height1 < -half_height || height1 > half_height)
		intersect->t1 = -1;
	if (height2 < -half_height || height2 > half_height)
		intersect->t2 = -1;
	if (vector_length(point[2] - cylinder->location - cylinder->vector * \
		half_height) > cylinder->radius || intersect->t_top < 0)
		intersect->t_top = -1;
	if (vector_length(point[3] - cylinder->location + cylinder->vector * \
		half_height) > cylinder->radius || intersect->t_bottom < 0)
		intersect->t_bottom = -1;
}

static float	closest_intersect_distance(float t1, float t2, \
											float t_top, float t_bottom)
{
	float	t_min;

	t_min = INFINITY;
	if (t1 > 0)
		t_min = fminf(t_min, t1);
	if (t2 > 0)
		t_min = fminf(t_min, t2);
	if (t_top > 0)
		t_min = fminf(t_min, t_top);
	if (t_bottom > 0)
		t_min = fminf(t_min, t_bottom);
	if (t_min < INFINITY)
		return (t_min);
	return (-1);
}

t_vec4f	intersect_cylinder(void *object, t_ray ray)
{
	const t_cylinder		*cylinder = (t_cylinder *)object;
	t_vec4f					result;
	t_cylinder_intersect	intersect;
	float					discriminant;

	discriminant = calculate_discriminant(ray, cylinder, &intersect);
	intersect.t1 = (-intersect.b - sqrtf(discriminant)) / (2 * intersect.a);
	intersect.t2 = (-intersect.b + sqrtf(discriminant)) / (2 * intersect.a);
	intersect.top_center = cylinder->location + \
							cylinder->vector * (cylinder->height / 2);
	intersect.bottom_center = cylinder->location - \
							cylinder->vector * (cylinder->height / 2);
	intersect.t_top = \
		dot3(intersect.top_center - ray.origin, cylinder->vector) \
		/ intersect.d_dot_v;
	intersect.t_bottom = dot3(intersect.bottom_center - ray.origin, \
						cylinder->vector) / intersect.d_dot_v;
	validate_intersect_distance(ray, cylinder, &intersect);
	intersect.t_min = closest_intersect_distance(intersect.t1, intersect.t2, \
						intersect.t_top, intersect.t_bottom);
	if (intersect.t_min == -1)
		return ((t_vec4f){0, 0, 0, -1});
	result = ray.origin + ray.direction * intersect.t_min;
	result[STATUS_INDEX] = CYLINDER;
	return (result);
}
