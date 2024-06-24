/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/06/24 15:49:28 by kwchu         ########   odam.nl         */
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

void	print_vec3(t_vec4f v, const char *msg)
{
	printf("%s [%.4f, %.4f, %.4f]\n", msg, v[0], v[1], v[2]);
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

// int	knuth_hash(void)
// {
// 	static int	seed;
	
// 	seed = ((seed + 1) * 2654435761) % (1 << 27);
// 	return (seed);
// }

int	knuth_hash(int *seed)
{
	*seed = ((*seed + 1) * 26761) % (1 << 27);
	return (*seed);
}

t_vec4f	generate_random_vec4f(void)
{
	static int	seed = 0;
	t_vec4f	vec4f;

	// vec4f = (t_vec4f){knuth_hash(&seed), knuth_hash(&seed), knuth_hash(&seed), 1};
	vec4f = (t_vec4f){knuth_hash(&seed), knuth_hash(&seed), knuth_hash(&seed), 1};
	normalize_vector(&vec4f);
	// print_vec3(vec4f, "random_vec");
	return (vec4f);
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

float	vector_length(t_vec4f v)
{
	return (sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

float	calculate_light_strength(float light_ratio, float distance, float light_strength)
{
	return (light_ratio / distance * light_strength);
}

t_vec4f	int_to_vec4rgb(int color)
{
	return ((t_vec4f){get_r(color), get_g(color), get_b(color), 0});
}

int	vec4rgb_to_int(t_vec4f vec)
{
	return ((int)vec[0] << 16 | (int)vec[1] << 8 | (int)vec[2]);
}

int	color_strength(int color, float strength)
{
	t_vec4f	rgb;

	rgb = int_to_vec4rgb(color);
	rgb *= strength;
	return (vec4rgb_to_int(rgb));
}

int	calculate_direct_light_intensity(t_scene_data *scene, int color, const t_vec4f point, t_vec4f normal)
{
	const t_vec4f	surface_to_light = scene->light.location - point;
	const float	strength = calculate_light_strength(scene->light.ratio, vector_length(surface_to_light), 2.0f);
	int			samples;
	t_ray		ray;
	t_vec4f		random;
	t_vec4f		rgb;

	samples = 32;
	ray.origin = point;
	// print_vec3(point, "point");
	normalize_vector(&normal);
	while (samples > 0)
	{
		ray.direction = generate_random_vec4f();
		// print_vec3(normal, "normal");
		// print_vec3(ray.origin, "ray origin");
		// print_vec3(ray.direction, "ray direction");
		// printf("[%.4f, %.4f, %.4f]\n", ray.direction[0], ray.direction[1], ray.direction[2]);
		if (dot_product_3d(normal, ray.direction) < 0.0f)
			ray.direction = -ray.direction;
		if (dot_product_3d(ray.direction, surface_to_light) >= 0.0f)
		{
			// printf("strength %.4f\n", strength);
			rgb = int_to_vec4rgb(color);
			// print_vec3(rgb, "rgb before");
			rgb *= strength;
			rgb += scene->ambient.ratio;
			// print_vec3(rgb, "rgb after strength");
			// rgb *= strength;
			rgb[0] = ft_min(ceilf(rgb[0]), 255);
			rgb[1] = ft_min(ceilf(rgb[1]), 255);
			rgb[2] = ft_min(ceilf(rgb[2]), 255);
			// print_vec3(rgb, "rgb after clamp");
			return (vec4rgb_to_int(rgb));
		}
		samples--;
	}
	// print_vec3(point, "point");
	// print_vec3(ray.direction, "ray direction");
	// if (point[1] < 0)
	// {
		// t_vec4f not_hit = (t_vec4f){255, 255, 255, 0};
		// return (vec4rgb_to_int(not_hit * fabsf(point[1] / 15)));
	// }
	return (color_strength(color, scene->ambient.ratio));
}

int	object_hit_color(t_scene_data *scene, const t_vec4f point)
{
	t_object	*current;

	current = scene->objects;
	while (current)
	{
		if (current->intersect(current->object, point - current->get_location(current->object)))
		{
			// if (current->type == SPHERE)
			// {
			// 	t_sphere *sphere;
			// 	sphere = current->object;
			// 	if (sphere->diameter == 1)
			// 		return (0xFFFFFF);
			// }
			if (current->intersect(current->object, scene->light.location - current->get_location(current->object)))
				return (0);
			// if (current->type == SPHERE)
			// 	return (visualize_sphere_normals(point, current->get_location(current->object)));
			return (calculate_direct_light_intensity(scene, current->get_color(current->object), point, point - current->get_location(current->object)));
		}
		current = current->next;	
	}
	return (-1);
}

int	color_at_ray(t_scene_data *scene, t_ray ray)
{
	t_vec4f			ray_point;
	const int		clipping_plane[2] = {5, 200};
	int				step;
	int				color;

	step = clipping_plane[0];
	ray_point = ray.origin + (float)step * ray.direction;
	while (step <= clipping_plane[1])
	{
		color = object_hit_color(scene, ray_point);
		if (color != -1)
			return (color);
		ray_point += ray.direction;
		step++;
	}
	return (-1);
}

t_ray	construct_camera_ray(float x, float y, t_scene_data *scene, const float aspect_ratio)
{
	t_ray		ray;
	float		pixel_camera_x;
	float		pixel_camera_y;
	const float	precision = 0.2f;

	ray.origin = scene->camera.location;
	pixel_camera_x = (2.0f * ((x + 0.5) / (float)scene->win_width) - 1) * tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f) * aspect_ratio;
	pixel_camera_y = (1.0f - 2.0f * ((y + 0.5) / (float)scene->win_height)) * tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f);
	ray.direction = (t_vec4f){pixel_camera_x, pixel_camera_y, -1, 1};
	// printf("before [%.4f, %.4f, %.4f]\n", ray.direction[0], ray.direction[1], ray.direction[2]);
	normalize_vector(&ray.direction);
	ray.direction *= precision;
	// printf("after [%.4f, %.4f, %.4f]\n", ray.direction[0], ray.direction[1], ray.direction[2]);
	return (ray);
}

void	visualise_light_location(t_object *current, t_light light)
{
	t_sphere	*sphere;

	sphere = NULL;
	while (current)
	{
		if (current->type != SPHERE)
			current = current->next;
		else
			sphere = (t_sphere *)current->object;
		if (sphere != NULL && sphere->diameter == 1)
		{
			sphere->location = light.location;
			break ;
		}
	}
}

void send_rays(t_scene_data *scene)
{
	const float	aspect_ratio = (float)scene->win_width / (float)scene->win_height;
	int		ray_x;
	int		ray_y;
	t_ray	ray;
	int 	color;

	// visualise_light_location(scene->objects, scene->light);
	ray_y = 0;
	while (ray_y < scene->win_height)
	{
		ray_x = 0;
		while (ray_x < scene->win_width)
		{
			color = -1;
			ray = construct_camera_ray((float)ray_x, (float)ray_y, scene, aspect_ratio);
			color = color_at_ray(scene, ray);
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
	print_vec3(scene->light.location, "light");
	print_vec3(scene->camera.location, "camera");
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