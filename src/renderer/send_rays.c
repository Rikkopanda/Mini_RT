/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/08/07 21:03:24 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

/**
 * make factor fall between 0 and 1
*/
void	fit_interpolation_range(float *rgb_factor)
{
	*rgb_factor += 1;
	*rgb_factor *= 0.5;
}

void	print_vec3(t_vec4f v, const char *msg)
{
	printf("%s [%.4f, %.4f, %.4f]\n", msg, v[0], v[1], v[2]);
}

void	print_vec4(t_vec4f v, const char *msg)
{
	printf("%s [%.4f, %.4f, %.4f, %.4f]\n", msg, v[0], v[1], v[2], v[3]);
}

void	moved_vector_position(t_vec4f *result, t_vec4f target_vec, t_vec4f offset)
{
	(*result) = target_vec - offset;
}

/**
 * @note Variation of Knuth's multiplicative method.
 */
float	knuth_hash(unsigned int *seed)
{
	*seed = ((*seed + 1) * 26761) % (1 << 27);
	return ((float)*seed / __INT_MAX__);
}
/**
 * @note Box-Muller transform to turn uniformly distributed random numbers 
 * to normal distributed
 * From: 
 */
float	random_normal_distribution(unsigned int *seed)
{
	const float	theta = 2 * M_PI * knuth_hash(seed);
	const float	rho = sqrtf(-2 * log(knuth_hash(seed)));

	return (rho * cos(theta));
}
/**
 * @note Unused at the moment, will be used for global illumination.
 */
t_vec4f	generate_random_vec4f(void)
{
	static unsigned int	seed = 0;
	t_vec4f				vec4f;

	vec4f = (t_vec4f){
		random_normal_distribution(&seed),
		random_normal_distribution(&seed),
		random_normal_distribution(&seed),
		1,
	};
	normalize_vector(&vec4f);
	return (vec4f);
}

float	calculate_light_strength(float ratio, float distance, float strength)
{
	return (ratio / distance * strength);
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

t_vec4f	invert_quaternion(t_vec4f quaternion)
{
	const float	squared = quaternion[0] * quaternion[0] + \
							quaternion[1] * quaternion[1] + \
							quaternion[2] * quaternion[2] + \
							quaternion[3] * quaternion[3];
	float		inverse;

	if (squared == 0.0f)
		return (quaternion);
	inverse = 1.0f / squared;
	return ((t_vec4f){
		quaternion[0] * inverse, \
		-quaternion[1] * inverse, \
		-quaternion[2] * inverse, \
		-quaternion[3] * inverse
	});
}

t_vec4f	invert_unit_quaternion(t_vec4f uq)
{
	return ((t_vec4f){uq[0], -uq[1], -uq[2], -uq[3]});
}

t_vec4f	axis_angle_to_quaternion(t_vec4f axis, float angle_rad)
{
	if (angle_rad == 0.0f)
		return ((t_vec4f){1, 0, 0, 0});
	return ((t_vec4f){
		cosf(angle_rad / 2), \
		axis[0] * sinf(angle_rad / 2),
		axis[1] * sinf(angle_rad / 2),
		axis[2] * sinf(angle_rad / 2)
	});
}
/**
 * @note multiplying quaternions according to Hamilton's product
 * Source: https://en.wikipedia.org/wiki/Quaternion#Hamilton_product
 * Source: https://www.meccanismocomplesso.org/en/hamiltons-quaternions-and-3d-rotation-with-python/
 */
t_vec4f	hamilton_product(t_vec4f q1, t_vec4f q2)
{
	t_vec4f	product;

	product[0] = q1[0] * q2[0] - \
				q1[1] * q2[1] - \
				q1[2] * q2[2] - \
				q1[3] * q2[3];
	product[1] = q1[0] * q2[1] + \
				q1[1] * q2[0] + \
				q1[2] * q2[3] - \
				q1[3] * q2[2];
	product[2] = q1[0] * q2[2] + \
				q1[2] * q2[0] + \
				q1[3] * q2[1] - \
				q1[1] * q2[3];
	product[3] = q1[0] * q2[3] + \
				q1[3] * q2[0] + \
				q1[1] * q2[2] - \
				q1[2] * q2[1];
	return (product);
}

t_vec4f combine_rotations(t_vec4f rotation)
{
	const t_vec4f q_x = axis_angle_to_quaternion((t_vec4f){1, 0, 0, 0}, \
												ft_degr_to_rad(rotation[0]));
	const t_vec4f q_y = axis_angle_to_quaternion((t_vec4f){0, 1, 0, 0}, \
												ft_degr_to_rad(rotation[1]));
	const t_vec4f q_z = axis_angle_to_quaternion((t_vec4f){0, 0, 1, 0}, \
												ft_degr_to_rad(rotation[2]));
	return (hamilton_product(hamilton_product(q_z, q_y), q_x));
}

/**
 * @note converts a point to a pure quaternion and applies rotation using the 
 * formula: P' = qpq*
 * P' = rotated point
 * q = the rotation quaternion (q_rotate)
 * q* = inverse of the rotation quaternion (q_inverse)
 * Source: https://danceswithcode.net/engineeringnotes/quaternions/quaternions.html
 * Source: https://www.youtube.com/watch?v=3BR8tK-LuB0
 */
t_vec4f	apply_rotation(t_vec4f point, t_vec4f rotation)
{
	const t_vec4f q_combined = combine_rotations(rotation);
	const t_vec4f quaternion_point = {0, point[0], point[1], point[2]};
	const t_vec4f q_inverse = invert_unit_quaternion(q_combined);
	const t_vec4f rotated_point = hamilton_product(hamilton_product(q_combined,\
												 quaternion_point), q_inverse);

	return ((t_vec4f){rotated_point[1], rotated_point[2], rotated_point[3], 1});
}

/**
 * @note Constructing a normalised camera ray from 
 * the x and y coordinates of a screen pixel.
 * From: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
 */
t_ray	construct_camera_ray(float x, float y, t_scene_data *scene, \
							const float aspect_ratio)
{
	t_ray		ray;
	float		pixel_camera_x;
	float		pixel_camera_y;
	const float	near_plane = 1e-1f;

	pixel_camera_x = (2.0f * ((x + 0.5) / (float)scene->win_width) - 1) * \
				tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f) * aspect_ratio;
	pixel_camera_y = (1.0f - 2.0f * ((y + 0.5) / (float)scene->win_height)) * \
				tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f);
	ray.direction = (t_vec4f){pixel_camera_x, pixel_camera_y, -1, 1};
	normalize_vector(&ray.direction);
	ray.direction = apply_rotation(ray.direction, scene->camera.orientation);
	ray.origin = scene->camera.location + ray.direction * near_plane;
	return (ray);
}

#include <time.h> 
#include <math.h>
#include <stdlib.h>

/**
 * @note Anti-aliasing sampling method, evenly distributes samples 
 * in a radius around the center pixel, raycenter in this case.
 * Returns the average color of all the samples.
 */
t_vec4f	sample_area(t_scene_data *scene, const float raycenter[2], \
					const float aspect_ratio, const float samples)
{
	t_ray		ray;
	t_vec4f		color;
	int			i;
	float		angle;
	float		inc;

	angle = 0;
	i = 0;
	color = (t_vec4f){0, 0, 0, -1};
	ray = construct_camera_ray(raycenter[0], raycenter[1], scene, aspect_ratio);
	color = trace_ray(scene, ray, 0);
	color *= 255;
	return color;
	if (samples != 0)
		inc = 2 * M_PI / samples;
	while (i < samples)
	{
		ray = construct_camera_ray(raycenter[0] + RADIUS * cos(angle), \
				raycenter[1] + RADIUS * sin(angle), scene, aspect_ratio);
		// color += int_to_vec4rgb(object_hit_color(scene, ray));
		angle += inc;
		i++;
	}
	// return (color / (samples + 1));
	return color;
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

/**
 * @note Samples are for anti-aliasing, higher = more accuracy.
 * Radius for anti-aliasing is defined in header.
 */
void send_rays(t_scene_data *scene)
{
	int			ray_x;
	int			ray_y;
	t_vec4f 	color;
	const float	aspect_ratio = (float)scene->win_width / scene->win_height;
	const int	samples = 2;
	t_vec4f camara_direction = apply_rotation((t_vec4f){0,0,-1,1}, scene->camera.orientation);
	printf("result camera direction:\t");
	print_matrix_1_3(camara_direction);
	// visualise_light_location(scene->objects, scene->light);
	ray_y = 0;
	while (ray_y < scene->win_height)
	{
		ray_x = 0;
		while (ray_x < scene->win_width)
		{
			color = sample_area(scene, (float[2]){ray_x, ray_y}, \
								aspect_ratio, samples);
			put_pixel_img(scene->image, ray_x, ray_y, vec4rgb_to_int(color));
			ray_x++;
			if (ray_x == scene->win_width - 1)
				printf("status bar %d, total: %d\n", ray_y * ray_x, scene->win_height * scene->win_width);
		}
		ray_y++;
	}
	print_vec3(scene->light.location, "light");
	print_vec3(scene->camera.location, "camera");
	print_vec3(scene->camera.orientation, "cam orientation");
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