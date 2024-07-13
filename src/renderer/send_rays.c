/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/07/13 16:21:48 by kwchu         ########   odam.nl         */
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

typedef struct s_hit_info
{
	t_object	*object;
	t_vec4f		hit_location;
	float		length;
	t_vec4f		color;
	t_vec4f		normal;
}	t_hit_info;

/**
 * @note Blinn-Phong shading model, different from regular Phong shading model.
 * Instead of light reflect & surface to cam vector, uses dot product 
 * of halfway vector & surface normal, which is cheaper to compute.
 * From: https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model &
 * https://www.youtube.com/watch?v=KdDdljGtfeg
 */
int	blinn_phong_shading(t_scene_data *scene, t_hit_info surface)
{
	const t_vec4f	surface_to_light = scene->light.location - surface.hit_location;
	const t_vec4f	surface_to_cam = scene->camera.location - surface.hit_location;
	const float		distance_to_light = vector_length(surface_to_light);
	const float		distance_to_cam = vector_length(surface_to_cam);
	const float		strength = scene->light.ratio / distance_to_light * 50.0f;
	t_vec4f			halfway_vec = (surface_to_light + surface_to_cam) / (distance_to_light + distance_to_cam);
	t_vec4f			diffuse;
	t_vec4f			specular;
	t_vec4f			ambient;
	const int		fac = 128;

	normalize_vector(&halfway_vec);
	ambient = (scene->ambient.ratio * scene->ambient.color.rgb_f + scene->ambient.ratio * surface.color) / 2;
	diffuse = ft_maxf(dot_product_3d(surface_to_light, surface.normal) / distance_to_light, 0.0f) * surface.color;
	const float spec_strength = 0.5f;
	specular = powf(ft_maxf(dot_product_3d(halfway_vec, surface.normal), 0.0f), fac) * scene->light.color.rgb_f * spec_strength;
	surface.color = (diffuse + specular) * strength + ambient;
	surface.color[0] = ft_min(surface.color[0], 255);
	surface.color[1] = ft_min(surface.color[1], 255);
	surface.color[2] = ft_min(surface.color[2], 255);
	return (vec4rgb_to_int(surface.color));
}

void	update_hit_info(t_hit_info *hit_info, t_vec4f hit, t_object *object, \
						float length)
{
	hit_info->hit_location = hit;
	hit_info->object = object;
	hit_info->length = length;
	hit_info->color = object->get_color(object->object);
	hit_info->normal = hit - object->get_location(object->object);
	normalize_vector(&hit_info->normal);
}

/**
 * @note Keeps track of closest intersection object.
 * bg_strength is used for the effect of the ambient color strength 
 * on the background, so it is different from the object's "shadow" color.
 */
int	object_hit_color(t_scene_data *scene, t_ray ray)
{
	t_object	*current;
	t_hit_info	closest_hit;
	t_vec4f		hit;
	float		length;
	const float	bg_strength = 0.2f;

	current = scene->objects;
	closest_hit.hit_location = (t_vec4f){0, 0, 0, -1};
	closest_hit.length = 200;
	while (current)
	{
		hit = current->intersect(current->object, ray);
		if (hit[3] != -1)
		{
			length = fabsf(vector_length(hit - ray.origin));
			if (length <= closest_hit.length)
				update_hit_info(&closest_hit, hit, current, length);
		}
		current = current->next;
	}
	if (closest_hit.hit_location[3] == -1)
		return (vec4rgb_to_int(scene->ambient.ratio * \
				scene->ambient.color.rgb_f * bg_strength));
	return (blinn_phong_shading(scene, closest_hit));
	
}

/**
 * @note Constructing a normalised camera ray from 
 * the x and y coordinates of a screen pixel.
 * From: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
 */
t_ray	construct_camera_ray(float x, float y, t_scene_data *scene, const float aspect_ratio)
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
	return (ray);
}

/**
 * @note Anti-aliasing sampling method, evenly distributes samples 
 * in a radius around the center pixel, rayf in this case.
 * Returns the average color of all the samples.
 */
t_vec4f	sample_area(t_scene_data *scene, const float rayf[2], \
					const float aspect_ratio, const float samples)
{
	t_ray		ray;
	t_vec4f		color;
	int			i;
	float		angle = 0.0;
	const float	inc = 2 * M_PI / samples;

	i = 0;
	color = (t_vec4f){0, 0, 0, -1};
	color += int_to_vec4rgb(object_hit_color(scene, \
							construct_camera_ray(rayf[0], rayf[1], \
							scene, aspect_ratio)));
	while (i < samples)
	{
		ray = construct_camera_ray(rayf[0] + RADIUS * cos(angle), \
				rayf[1] + RADIUS * sin(angle), scene, aspect_ratio);
		color += int_to_vec4rgb(object_hit_color(scene, ray));
		angle += inc;
		i++;
	}
	return (color / (samples + 1));
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
	const int	samples = 16;

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
		}
		ray_y++;
	}
	print_vec3(scene->light.location, "light");
	print_vec3(scene->camera.location, "camera");
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