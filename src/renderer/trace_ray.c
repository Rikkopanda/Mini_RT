/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:19:30 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 17:45:30 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mini_math.h"

/**
 * reflection() uses old the old ray.origin, this is the incident ray
 */
t_vec4f	compute_incoming_light(t_scene_data *scene, t_ray ray, \
	t_hit_info *hit_info, int bounce_depth)
{
	t_vec4f		incoming_light_color;
	t_vec4f		incident_ray;
	t_vec4f		diffuse_ray;
	t_vec4f		reflection;
	int			i;

	i = 0;
	incoming_light_color = (t_vec4f){0, 0, 0, 0};
	while (i < REFL_RAYS_N)
	{
		incident_ray = hit_info->hit_location - hit_info->incident_origin;
		normalize_vector(&incident_ray);
		diffuse_ray = generate_random_vec4f_hemisphere(hit_info->normal);
		normalize_vector(&diffuse_ray);
		reflection = reflect(hit_info->normal, incident_ray);
		ray.direction = lerp(diffuse_ray, reflection, \
			hit_info->material.smoothness);
		normalize_vector(&ray.direction);
		incoming_light_color += (trace_ray(scene, ray, bounce_depth + 1));
		i++;
	}
	return (incoming_light_color);
}

/**
 * rendering equation(NVIDIA's uitleg):
 * https://www.youtube.com/watch?v=AODo_RjJoUA
 * 
 * Josh's Channel
 * https://www.youtube.com/watch?v=gsZiJeaMO48&t=274s
 * 
 * https://www.umb.edu/spectralmass/terra-aqua-modis/modis/
 * 
 * rendering equation intuitieve animatie
 * https://www.youtube.com/watch?v=eo_MTI-d28s
 * 
 * file:///home/rverhoev/Downloads/ray_tracing_practice.pdf
 * 
 * lange uitleg
 * https://www.youtube.com/watch?v=wawf7Am6xy0
 * 
 */
t_vec4f	trace_ray(t_scene_data *scene, t_ray ray, int bounce_depth)
{
	t_hit_info	hit_info;
	t_vec4f		light_in;
	t_vec4f		incident_origin;
	t_vec4f		result_color;

	hit_info.incident_origin = ray.origin;
	check_intersection(scene, ray, &hit_info, bounce_depth);
	ray.origin = hit_info.hit_location;
	if (hit_info.type == NONE)
	{
		if (bounce_depth == 0)
			return (sky_box(ray.direction[1]) / 255);
		else
			return ((sky_box(ray.direction[1]) / 255) * scene->ambient.ratio);
	}
	else if (bounce_depth == MAX_BOUNCE_DEPTH)
		return (hit_info.emission);
	else if (hit_info.type == LIGHT)
		return (hit_info.emission);
	light_in = compute_incoming_light(scene, ray, &hit_info, bounce_depth);
	result_color = (hit_info.material.color / 255) * (light_in / REFL_RAYS_N);
	result_color += hit_info.emission;
	result_color = clamp_vec4f(result_color, 0, 1);
	return (result_color);
}
