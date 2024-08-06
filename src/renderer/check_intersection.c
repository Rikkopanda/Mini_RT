
#include "minirt.h"

void	update_hit_info(t_hit_info *hit_info, t_vec4f hit, t_object *object, \
						float length);

/**
 * @note Keeps track of closest intersection object.
 * bg_strength is used for the effect of the ambient color strength 
 * on the background, so it is different from the object's "shadow" color.
 * 
 * 
 * 	0.0 smoothness means * 1
 *  1.0 smoothness means * 0
 */
void	check_intersection(t_scene_data *scene, t_ray ray, t_hit_info	*closest_hit, int depth)
{
	t_object	*current;
	t_vec4f		hit;
	float		length;
	const float	bg_strength = 0.2f;

	current = scene->objects;
	closest_hit->hit_location = (t_vec4f){0, 0, 0, -1};
	closest_hit->length = 800;
	closest_hit->type = NONE;
	while (current)
	{
		// if (depth != 0)
		// 	print_matrix_1_3(ray.direction);
		// printf("intersect f: %p\n", current->intersect);
		hit = current->intersect(current->object, ray);
		if (hit[STATUS_INDEX] != -1)
		{
			length = fabsf(vector_length(hit - ray.origin)); // fabs omdat we ook in de negatieve richting kunnen kijken als de camera zo staat?
			if (length <= closest_hit->length)
				update_hit_info(closest_hit, hit, current, length);
			// if (closest_hit->type == LIGHT)
			// {
				// print_matrix_1_3(closest_hit->material.color);
			// }
			// if (depth != 0)
			// 	printf("type: %d\n", current->type);
		}
		current = current->next;
	}
}

void	update_hit_info(t_hit_info *hit_info, t_vec4f hit, t_object *object, \
						float length)
{
	hit_info->hit_location = hit;
	hit_info->object = object;
	hit_info->length = length;
	hit_info->type = object->type;
	hit_info->material.color = object->get_color(object->object);
	if (object->type != LIGHT)
		hit_info->material.smoothness = object->get_smoothness(object->object);
	if (object->type == LIGHT)
	{
		t_vec4f light_color = object->get_color(object->object);
		light_color /= 255;
		hit_info->emission = (object->get_brightness(object->object) * 10) * light_color;
		// hit_info->emission = light_color;
	}
	else
		hit_info->emission = (t_vec4f){0,0,0,0};
	// if (hit_info->material.smoothness > 0)
	// 	printf("smoothness %f\n", hit_info->material.smoothness);
	t_vec4f obj_center = object->get_location(object->object);
	hit_info->normal = hit - object->get_location(object->object);
	normalize_vector(&hit_info->normal);
}