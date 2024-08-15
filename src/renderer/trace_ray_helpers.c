/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace_ray_helpers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 15:19:11 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/08/15 14:16:22 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

t_vec4f	generate_random_vec4f_hemisphere(t_vec4f normal)
{
	t_vec4f	random_vec;

	srand(time(0));
	random_vec[0] = (float)rand();
	random_vec[1] = (float)rand();
	random_vec[2] = (float)rand();
	random_vec[3] = 0.0f;
	normalize_vector(&random_vec);
	if (dot3(random_vec, normal) < 0.0f)
	{
		random_vec *= -1.0f;
	}
	return (random_vec);
}

t_vec4f	reflect(t_vec4f normal, t_vec4f incoming)
{
	t_vec4f	reflection;

	reflection = incoming - (2 * dot3(incoming, normal) * normal);
	return (reflection);
}

t_vec4f	lerp(t_vec4f a, t_vec4f b, float f)
{
	if (f == 0)
		return (a);
	else if (f == 1)
		return (b);
	else
		return ((a * (float)(1.0 - f)) + (b * f));
}

t_vec4f	sky_box(float y)
{
	const t_vec4f	top_hemi = (t_vec4f){145, 224, 255, -1};
	const t_vec4f	bottom_hemi = (t_vec4f){255, 255, 255, -1};
	t_vec4f			result;

	if (y > 0.1)
		return (top_hemi);
	else if (y < -0.1)
		return (bottom_hemi);
	result = lerp(bottom_hemi, top_hemi, (y + 0.1f) / 0.2f);
	result[3] = NONE;
	return (result);
}
