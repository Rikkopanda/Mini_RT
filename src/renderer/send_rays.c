/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/09 12:14:33 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include <time.h> 
#include <math.h>
#include <stdlib.h>

/**
 * @note Constructing a normalised camera ray from 
 * the x and y coordinates of a screen pixel.
 * From: https://www.scratchapixel.com/lessons/3d-bas
 * ic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
 */
t_ray	construct_camera_ray(float x, float y, t_scene_data *scene, \
							const float aspect_ratio)
{
	t_ray		ray;
	float		pixel_camera_x;
	float		pixel_camera_y;

	ray.origin = scene->camera.location;
	pixel_camera_x = (2.0f * ((x + 0.5) / (float)scene->win_width) - 1) * \
				tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f) * aspect_ratio;
	pixel_camera_y = (1.0f - 2.0f * ((y + 0.5) / (float)scene->win_height)) * \
				tanf(ft_degr_to_rad(scene->camera.fov) * 0.5f);
	ray.direction = (t_vec4f){pixel_camera_x, pixel_camera_y, -1, 1};
	normalize_vector(&ray.direction);
	ray.direction = apply_rotation(ray.direction, scene->camera.orientation);
	return (ray);
}

/**
 * @note Anti-aliasing sampling method, evenly distributes samples 
 * in a radius around the center pixel, raycenter in this case.
 * Returns the average color of all the samples.
 */
// t_vec4f	sample_area(t_scene_data *scene, const float raycenter[2], \
// 					const float aspect_ratio, const float samples)
// {
// 	t_ray		ray;
// 	t_vec4f		color;
// 	int			i;
// 	float		angle;
// 	const float	inc = 2 * M_PI / samples;

// 	angle = 0;
// 	i = 0;
// 	color = (t_vec4f){0, 0, 0, -1};
// 	ray = construct_camera_ray(raycenter[0], raycenter[1], scene, aspect_ratio);
// 	color = trace_ray(scene, ray, 0);
// 	color *= 255;
// 	return color;
// 	while (i < samples)
// 	{
// 		ray = construct_camera_ray(raycenter[0] + RADIUS * cos(angle), \
// 				raycenter[1] + RADIUS * sin(angle), scene, aspect_ratio);
// 		// color += int_to_vec4rgb(object_hit_color(scene, ray));
// 		angle += inc;
// 		i++;
// 	}
// 	// return (color / (samples + 1));
// 	return color;
// }

t_vec4f	shoot_ray(t_scene_data *scene, const float raycenter[2], \
					const float aspect_ratio, const float samples)
{
	t_ray		ray;
	t_vec4f		color;

	color = (t_vec4f){0, 0, 0, -1};
	ray = construct_camera_ray(raycenter[0], raycenter[1], scene, aspect_ratio);
	color = trace_ray(scene, ray, 0);
	color *= 255;
	return (color);
}

/**
 * @note Samples are for anti-aliasing, higher = more accuracy.
 * Radius for anti-aliasing is defined in header.
 */
void	send_rays(t_scene_data *scene)
{
	int			ray_x;
	int			ray_y;
	t_vec4f		color;
	const float	aspect_ratio = (float)scene->win_width / scene->win_height;
	const int	samples = 2;

	ray_y = 0;
	while (ray_y < scene->win_height)
	{
		ray_x = 0;
		while (ray_x < scene->win_width)
		{
			color = shoot_ray(scene, (float [2]){ray_x, ray_y}, \
								aspect_ratio, samples);
			put_pixel_img(scene->image, ray_x, ray_y, vec4rgb_to_int(color));
			ray_x++;
			if (PRINT_STATUS)
				printf("status bar %d, total: %d\n", ray_y * ray_x, \
					scene->win_height * scene->win_width);
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
*/