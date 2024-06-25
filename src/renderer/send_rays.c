/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   send_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/06/25 17:51:40 by kwchu         ########   odam.nl         */
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

t_vec4f	specular_highlight(t_vec4f color, float cos_theta, float light_strength)
{
	const t_vec4f	white = (t_vec4f){255, 255, 255, 1};

	color = light_strength * white * cos_theta;
	color[0] = ft_min(color[0], 255);
	color[1] = ft_min(color[1], 255);
	color[2] = ft_min(color[2], 255);
	return (color);
}

int	calculate_direct_light_intensity(t_scene_data *scene, int color, const t_vec4f point, t_vec4f normal)
{
	const t_vec4f	surface_to_light = scene->light.location - point;
	const float		distance_to_light = vector_length(surface_to_light);
	const float	strength = calculate_light_strength(scene->light.ratio, \
							distance_to_light, 50.0f);
	int			samples;
	t_ray		ray;
	t_vec4f		random;
	t_vec4f		rgb;
	const int	max = 25;

	samples = 600;
	ray.origin = point;
	// print_vec3(point, "point");
	normalize_vector(&normal);
	// if (strength >= 1.0f)
	// 	printf("%.4f\n", strength);
	while (samples > 0)
	{
		// ray.direction = generate_random_vec4f();
		// // print_vec3(normal, "normal");
		// // print_vec3(ray.origin, "ray origin");
		// // printf("[%.4f, %.4f, %.4f]\n", ray.direction[0], ray.direction[1], ray.direction[2]);
		// if (dot_product_3d(normal, ray.direction) < 0.0f)
		// 	ray.direction = -ray.direction;
		if (dot_product_3d(normal, surface_to_light) > 0.0f)
		{
			float	cos_theta = dot_product_3d(surface_to_light, normal) / distance_to_light;
			// float attenuation = 1.0f / (1.0f + 0.1f * distance_to_light * distance_to_light);
			cos_theta = ft_maxf(cos_theta, 0.0f);
			t_vec4f	surface_to_cam = scene->camera.location - point;
			float	distance_to_cam = vector_length(surface_to_cam);
			t_vec4f	halfway_vec = (surface_to_light + surface_to_cam) / (distance_to_light + distance_to_cam);
			normalize_vector(&halfway_vec);
			float	specular = ft_maxf(dot_product_3d(halfway_vec, normal), 0.0f);
			// print_vec3(ray.direction, "ray direction");
			// printf("strength %.4f\n", strength);
			// print_vec3(rgb, "rgb before");
			// printf("ambient %.4f\n", scene->ambient.ratio);
			// // print_vec3(rgb, "rgb after strength");
			rgb = int_to_vec4rgb(color);
			rgb = (rgb * strength) * cos_theta + (rgb * scene->ambient.ratio);
			rgb[0] = ft_min(rgb[0], get_r(color));
			rgb[1] = ft_min(rgb[1], get_g(color));
			rgb[2] = ft_min(rgb[2], get_b(color));
			// rgb = (t_vec4f){0, 0, 0, 1};
			// printf("specular %.4f\n", specular);
			// printf("cos_theta %.4f\n", cos_theta);
			rgb = rgb + (powf((specular), 128) * 255 / (distance_to_light * 0.03f));
			// print_vec3(rgb, "rgb after specular");
			rgb[0] = ft_min(rgb[0], 255);
			rgb[1] = ft_min(rgb[1], 255);
			rgb[2] = ft_min(rgb[2], 255);
			// if (point[0] >= -0.5f && point[0] <= 0.5f)
			
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
	int shadow_color = color_strength(color, scene->ambient.ratio);
	// printf("shadow color %X\n", shadow_color);
	return (shadow_color);
}

int	object_hit_color(t_scene_data *scene, t_ray ray)
{
	t_object	*current;
	t_vec4f		hit_location;
	t_vec4f		closest_hit;
	t_object	*closest_object;
	float		closest_length;
	float		current_length;

	current = scene->objects;
	closest_hit = (t_vec4f){0, 0, 0, -1};
	closest_length = 200;
	while (current)
	{
		hit_location = current->intersect(current->object, ray);
		if (hit_location[3] != -1)
		{
			current_length = fabsf(vector_length(hit_location - scene->camera.location));
			if (current_length <= closest_length)
			{
				closest_length = current_length;
				closest_hit = hit_location;
				closest_object = current;
			}
		}
		current = current->next;
	}
	if (closest_hit[3] == -1)
		return (-1);
	return (calculate_direct_light_intensity(scene, closest_object->get_color(closest_object->object), \
			closest_hit, closest_hit - closest_object->get_location(closest_object->object)));
	
}

int	color_at_ray(t_scene_data *scene, t_ray ray)
{
	int				color;

	color = object_hit_color(scene, ray);
	if (color != -1)
		return (color);
	return (-1);
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
				put_pixel_img(scene->image, ray_x, ray_y, vec4rgb_to_int(scene->ambient.ratio * (t_vec4f){scene->ambient.color.rgb[0], scene->ambient.color.rgb[1], scene->ambient.color.rgb[2], 1}));
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