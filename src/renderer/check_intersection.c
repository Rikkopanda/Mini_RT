/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:23:38 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 17:56:42 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_hit_info(t_hit_info *hit_info, t_vec4f hit, \
			t_object *object, float length);

/**
 * @note Keeps track of closest intersection object.
 * bg_strength is used for the effect of the ambient color strength 
 * on the background, so it is different from the object's "shadow" color.
 * 
 * 
 * 	0.0 smoothness means * 1
 *  1.0 smoothness means * 0
 */
void	check_intersection(t_scene_data *scene, t_ray ray, \
			t_hit_info *closest_hit)
{
	t_object	*current;
	t_vec4f		hit;
	float		length;

	current = scene->objects;
	closest_hit->hit_location = (t_vec4f){0, 0, 0, -1};
	closest_hit->length = 800;
	closest_hit->type = NONE;
	while (current)
	{
		hit = current->intersect(current->object, ray);
		if (hit[STATUS_INDEX] != -1)
		{
			length = fabsf(vector_length(hit - ray.origin));
			if (length <= closest_hit->length)
				update_hit_info(closest_hit, hit, current, length);
		}
		current = current->next;
	}
}

void	update_hit_info(t_hit_info *hit_info, t_vec4f hit, t_object *object, \
						float length)
{
	t_vec4f	light_color;

	hit_info->hit_location = hit;
	hit_info->object = object;
	hit_info->length = length;
	hit_info->type = object->type;
	hit_info->material.color = object->get_color(object->object);
	if (object->type != LIGHT)
		hit_info->material.smoothness = object->get_smoothness(object->object);
	if (object->type == LIGHT)
	{
		light_color = object->get_color(object->object);
		light_color /= 255;
		hit_info->emission = (object->get_brightness(object->object) \
			* 10) * light_color;
	}
	else
		hit_info->emission = (t_vec4f){0, 0, 0, 0};
	if (object->type != LIGHT)
		hit_info->normal = object->get_normal(object->object, hit);
	normalize_vector(&hit_info->normal);
}
