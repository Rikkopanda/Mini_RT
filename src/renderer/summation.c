/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/07/29 17:53:37 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

/**
 * raytrace color summation with the sum of all reflected rays return value;
 * this could be directly a light source or another object.
 * 
 * if its another object this proces happens on that surface, the result color is then returned 
 * to the calling trace function, which is the origin place of that ray.
 */
t_vec4f	ray_trace_coloring(t_scene_data *scene, t_vec4f color_bounce_sum, t_vec4f emmisive_light_color_sum, t_hit_info surface)
{
	const t_vec4f	surface_to_light = scene->light.location - surface.hit_location;
	const t_vec4f	surface_to_cam = scene->camera.location - surface.hit_location;
	const float		distance_to_light = vector_length(surface_to_light);
	const float		distance_to_cam = vector_length(surface_to_cam);
	const float		strength = scene->light.ratio / distance_to_light * 50.0f; // ratio == brightness
	t_vec4f			halfway_vec = (surface_to_light + surface_to_cam) / (distance_to_light + distance_to_cam); // wat doet de / (dist1 + dist2)  als je toch gaat normalizen?
	t_vec4f			diffuse;
	t_vec4f			specular;
	t_vec4f			ambient;
	const int		fac = 128;

	normalize_vector(&halfway_vec);
	ambient = (scene->ambient.ratio * scene->ambient.color.rgb_f + scene->ambient.ratio * surface.material.color) / 2;
	diffuse = ((color_bounce_sum + surface.material.color) / 2);// light kleur van invloed nu

	// diffuse = (ft_maxf(dot_product_3d(surface_to_light, surface.normal) / distance_to_light, 0.0f) * surface.material.color) * scene->light.color.rgb_f;// light kleur van invloed nu
	const float spec_strength = 0.5f;
	// specular = powf(ft_maxf(dot_product_3d(halfway_vec, surface.normal), 0.0f), fac) * scene->light.color.rgb_f * spec_strength;

	// surface.material.color = ((diffuse + specular) * strength + ambient);// hoe is de voorrang van haakjes?
	// normalize_vector(&emmisive_light_color_sum);
	surface.material.color = ambient + (diffuse * emmisive_light_color_sum);
	surface.material.color[0] = ft_min(surface.material.color[0], 255);
	surface.material.color[1] = ft_min(surface.material.color[1], 255);
	surface.material.color[2] = ft_min(surface.material.color[2], 255);// kleuren tussen float 0 - 255 ?
	return (surface.material.color);
}