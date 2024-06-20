/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/06/20 17:06:59 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

/**
 * make factor fall between 0 and 1
*/
void fit_interpolation_range(float *rgb_factor)
{
	*rgb_factor += 1;
	*rgb_factor *= 0.5;
}


/**
 * vector from point A to point B
*/

void moved_vector_position(t_vec4f *result, t_vec4f target_vec, t_vec4f offset)
{
	(*result) = target_vec - offset; 
}

// int	sphere_intersection_equation(t_scene_data *data, t_vec4f obj_to_ray_vec)
// {
// 	const float squared = powf(obj_to_ray_vec[0], 2) + powf(obj_to_ray_vec[1], 2) + powf(obj_to_ray_vec[2], 2);

// 	if (sqrtf(squared) <= data->sphere.radius)
// 		return (TRUE);
// 	else
// 		return (FALSE);
// }

float	dot_product_3d(t_vec4f vec_A, t_vec4f vec_B)
{
	return ((vec_A[0] * vec_B[0]) + (vec_A[1] * vec_B[1]) + (vec_A[2] * vec_B[2]));
}

float	cross_product_3d(t_vec4f vec_A, t_vec4f vec_B)
{
	return ((vec_A[2] * vec_B[3]) - (vec_B[2] * vec_A[3]) +
			(vec_A[3] * vec_B[1]) - (vec_B[3] * vec_A[1]) +
			(vec_A[1] * vec_B[2]) - (vec_B[1] * vec_A[2]));
}

int visualize_sphere_normals(const t_vec4f point, t_vec4f center)
{
	t_vec4f	normal;
	int	rgb[3];

	normal = point - center;
	normalize_vector(&normal);
	normal = normal * 0.5f + 0.5f;
	make_rgb_with_normalized_rgb_f(rgb, normal);
	return (create_color(rgb[0], rgb[1], rgb[2]));
}

int	object_hit_color(t_object *current, const t_vec4f point)
{
	while (current)
	{
		if (current->intersect(current->object, point - current->get_location(current->object)))
		{
			if (current->type == SPHERE)
				return (visualize_sphere_normals(point, current->get_location(current->object)));
			return (current->get_color(current->object));
		}
		current = current->next;	
	}
	return (-1);
}

int	color_at_ray(t_object *objects, t_ray ray)
{
	t_vec4f			ray_point;
	const t_vec4f	ray_step = ray.direction;
	const int		clipping_plane[2] = {1, 200};
	int				step;
	int				color;

	step = clipping_plane[0];
	ray_point = ray.origin + (float)step * ray_step;
	while (step <= clipping_plane[1])
	{
		color = object_hit_color(objects, ray_point);
		if (color != -1)
			return (color);
		ray_point += ray_step;
		step++;
	}
	return (-1);
}

t_ray	construct_ray(float x, float y, t_scene_data *scene, const float aspect_ratio)
{
	t_ray	ray;
	float	pixel_camera_x;
	float	pixel_camera_y;

	ray.origin = (t_vec4f){0, 0, 0, 0};
	pixel_camera_x = (2.0f * ((x + 0.5) / (float)scene->win_width) - 1) * tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f) * aspect_ratio;
	pixel_camera_y = (1.0f - 2.0f * ((y + 0.5) / (float)scene->win_height)) * tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f);
	ray.direction = (t_vec4f){pixel_camera_x, pixel_camera_y, -0.5, 0};
	ray.origin += scene->camera.location;
	return (ray);
}

void send_rays(t_scene_data *scene)
{
	int		ray_x;
	int		ray_y;
	t_ray	ray;
	int 	color;
	const float	aspect_ratio = (float)scene->win_width / (float)scene->win_height;

	ray_y = 0;
	while (ray_y < scene->win_height)
	{
		ray_x = 0;
		while (ray_x < scene->win_width)
		{
			color = -1;
			ray = construct_ray((float)ray_x, (float)ray_y, scene, aspect_ratio);
			color = color_at_ray(scene->objects, ray);
			// printf("[%.4f, %.4f, %.4f]\n", ray.direction[0], ray.direction[1], ray.direction[2]);
			if (color != -1)
				put_pixel_img(scene->image, ray_x, ray_y, color);
			else
				put_pixel_img(scene->image, ray_x, ray_y, 0);
			ray_x++;
		}
		ray_y++;
	}
	printf("done\n");
}
/*
clock_t				t;
t = clock();
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
printf("The program took %f seconds to execute\n
", time_taken);
// printf("angles horizontal, vertical: 1  %f\t%f\n", ft_rad_to_degr(r_t.angle_horiz), ft_rad_to_degr(r_t.angle_vert));
// printf("perp hori %f\n", r_t.perpendicular_distance_horiz_triangle);
// printf("perp verti %f\n", r_t.perpendicular_distance_vert_triangle);
// printf("screen half %d\n, ", r_t.half_screen_width);

// if (PRINT_DEBUG) printf("angles horizontal, vertical: 1  %f\t%f\n", ft_rad_to_degr(r_t.angle_horiz), ft_rad_to_degr(r_t.angle_vert));
// printf("perp hori %f\n", r_t.perpendicular_distance_horiz_triangle);
// printf("perp verti %f\n", r_t.perpendicular_distance_vert_triangle);
// printf("screen half %d\n, ", r_t.half_screen_width);
// sleep(1);
*/