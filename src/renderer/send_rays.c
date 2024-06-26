/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/06/26 16:58:34 by kwchu         ########   odam.nl         */
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

// int	knuth_hash(void)
// {
// 	static int	seed;
	
// 	seed = ((seed + 1) * 2654435761) % (1 << 27);
// 	return (seed);
// }
#include <limits.h>

float	knuth_hash(unsigned int *seed)
{
	*seed = ((*seed + 1) * 26761) % (1 << 27);
	return ((float)*seed / INT_MAX);
}

float	knuth_hash_normal_distribution(unsigned int *seed)
{
	const float	theta = 2 * M_PI * knuth_hash(seed);
	const float	rho = sqrtf(-2 * log(knuth_hash(seed)));

	// printf("theta %.4f\n", theta);
	// printf("rho %.4f\n", rho);
	return (rho * cos(theta));
};

t_vec4f	generate_random_vec4f(void)
{
	t_vec4f		vec4f;
	static unsigned int	seed = 0;

	// vec4f = (t_vec4f){knuth_hash(&seed), knuth_hash(&seed), knuth_hash(&seed), 1};
	vec4f = (t_vec4f){knuth_hash_normal_distribution(&seed), knuth_hash_normal_distribution(&seed), knuth_hash_normal_distribution(&seed), 1};
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

float	calculate_light_strength(float light_ratio, float distance, float light_strength)
{
	return (light_ratio / distance * light_strength);
}

int	color_strength(int color, float strength)
{
	t_vec4f	rgb;

	rgb = int_to_vec4rgb(color);
	rgb *= strength;
	rgb[0] = ft_min(rgb[0], 255);
	rgb[1] = ft_min(rgb[1], 255);
	rgb[2] = ft_min(rgb[2], 255);
	return (vec4rgb_to_int(rgb));
}

float	ft_maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

int	calculate_direct_light_intensity(t_scene_data *scene, t_vec4f color, const t_vec4f point, t_vec4f normal)
{
	const t_vec4f	surface_to_light = scene->light.location - point;
	const t_vec4f	surface_to_cam = scene->camera.location - point;
	const float		distance_to_light = vector_length(surface_to_light);
	const float		distance_to_cam = vector_length(surface_to_cam);
	const float		strength = calculate_light_strength(scene->light.ratio, \
								distance_to_light, 150.0f);
	t_vec4f			halfway_vec = (surface_to_light + surface_to_cam) / (distance_to_light + distance_to_cam);
	t_vec4f			diffuse;
	t_vec4f			specular;
	t_vec4f			ambient;
	const int		fac = 128;

	normalize_vector(&normal);
	normalize_vector(&halfway_vec);
	ambient = scene->ambient.ratio * color;
	// printf("strength %.4f\n", strength);
	// print_vec3(ambient, "ambient");
	diffuse = ft_maxf(dot_product_3d(surface_to_light, normal) / distance_to_light, 0.0f) * color;
	// print_vec3(diffuse, "diffuse");
	const float spec_strength = 0.5f;
	specular = powf(ft_maxf(dot_product_3d(halfway_vec, normal), 0.0f), fac) * scene->light.color.rgb_f * spec_strength;
	// print_vec3(specular, "specular");
	color = (diffuse + specular) * strength / (distance_to_light * 0.03f) + ambient;
	// print_vec3(color, "color");
	color[0] = ft_min(color[0], 255);
	color[1] = ft_min(color[1], 255);
	color[2] = ft_min(color[2], 255);
	return (vec4rgb_to_int(color));
}

int	object_hit_color(t_scene_data *scene, t_ray ray, t_vec4f *closest_hit)
{
	t_object	*current;
	t_vec4f		hit_location;
	t_object	*closest_object;
	float		closest_length;
	float		current_length;

	current = scene->objects;
	closest_length = 200;
	while (current)
	{
		hit_location = current->intersect(current->object, ray);
		if (hit_location[3] != -1)
		{
			// if (current->type == SPHERE)
			// {
			// 	t_sphere *sphere = current->object;
			// 	if (sphere->diameter == 1)
			// 		return (0xFFFFFF);
			// }
			current_length = fabsf(vector_length(hit_location - scene->camera.location));
			if (current_length <= closest_length)
			{
				closest_length = current_length;
				*closest_hit = hit_location;
				closest_object = current;
			}
		}
		current = current->next;
	}
	if ((*closest_hit)[3] == -1)
		return (-1);
	return (calculate_direct_light_intensity(scene, closest_object->get_color(closest_object->object), \
			*closest_hit, *closest_hit - closest_object->get_location(closest_object->object)));
	
}

t_ray	construct_camera_ray(float x, float y, t_scene_data *scene, const float aspect_ratio)
{
	t_ray		ray;
	float		pixel_camera_x;
	float		pixel_camera_y;

	ray.origin = scene->camera.location;
	pixel_camera_x = (2.0f * ((x + 0.5) / (float)scene->win_width) - 1) * tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f) * aspect_ratio;
	pixel_camera_y = (1.0f - 2.0f * ((y + 0.5) / (float)scene->win_height)) * tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f);
	ray.direction = (t_vec4f){pixel_camera_x, pixel_camera_y, -1, 1};
	normalize_vector(&ray.direction);
	return (ray);
}

t_vec4f	sample_area(t_scene_data *scene, float ray_x, float ray_y, const float aspect_ratio)
{
	t_ray		ray;
	t_ray		offset_ray;
	int			center_color;
	t_vec4f		color;
	t_vec4f		hit_location;
	int			sample_color;
	int			i;
	const float	offset = 0.5;
	float		sample_offset[2][4] = {
		{offset, offset, -offset, -offset},
		{offset, -offset, offset, -offset},
	};

	i = 0;
	color = (t_vec4f){0, 0, 0, -1};
	ray = construct_camera_ray(ray_x, ray_y, scene, aspect_ratio);
	hit_location = (t_vec4f){0, 0, 0, -1};
	center_color = object_hit_color(scene, ray, &hit_location);
	if (center_color == -1)
		return (color);
	while (i < SAMPLES)
	{
		hit_location = (t_vec4f){0, 0, 0, -1};
		offset_ray = construct_camera_ray(ray_x + sample_offset[0][i], ray_y + sample_offset[1][i], scene, aspect_ratio);
		// offset_ray.direction += generate_random_vec4f() * 0.001f;
		// print_vec3(ray.direction, "original dir");
		// print_vec3(offset_ray.direction, "offset dir");
		sample_color = object_hit_color(scene, offset_ray, &hit_location);
		if (sample_color == -1)
			sample_color = vec4rgb_to_int(scene->ambient.ratio * scene->ambient.color.rgb_f);
		color += int_to_vec4rgb(sample_color);
		i++;
	}
	color += int_to_vec4rgb(center_color);
	return (color / (SAMPLES + 1));
}

void	visualise_light_location(t_object *current, t_light light)
{
	t_sphere	*sphere;

	sphere = NULL;
	while (current)
	{
		if (current->type == SPHERE)
			sphere = (t_sphere *)current->object;
		if (sphere != NULL && sphere->diameter == 1)
		{
			sphere->location = light.location;
			break ;
		}
		current = current->next;
	}
}

void send_rays(t_scene_data *scene)
{
	int			ray_x;
	int			ray_y;
	t_vec4f 	color;
	const float	aspect_ratio = (float)scene->win_width / scene->win_height;
	const int	samples = 4;

	// visualise_light_location(scene->objects, scene->light);
	ray_y = 0;
	while (ray_y < scene->win_height)
	{
		ray_x = 0;
		while (ray_x < scene->win_width)
		{
			color = sample_area(scene, (float)ray_x, (float)ray_y, aspect_ratio);
			// printf("[%.4f, %.4f, %.4f]\n", ray.direction[0], ray.direction[1], ray.direction[2]);
			if (color[3] != -1)
				put_pixel_img(scene->image, ray_x, ray_y, vec4rgb_to_int(color));
			else
				put_pixel_img(scene->image, ray_x, ray_y, vec4rgb_to_int(scene->ambient.ratio * scene->ambient.color.rgb_f));
			// 	put_pixel_img(scene->image, ray_x, ray_y, 0xFFFFFF);
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