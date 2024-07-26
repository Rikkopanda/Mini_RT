/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/07/26 15:00:14 by rverhoev         ###   ########.fr       */
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

typedef struct s_material
{
	float		smoothness;
	t_vec4f		color;
} t_material;


typedef struct s_hit_info
{
	t_object	*object;
	t_vec4f		hit_location;
	float		length;
	t_vec4f		normal;
	t_material	material;
}	t_hit_info;

/**
 * @note Blinn-Phong shading model, different from regular Phong shading model.
 * Instead of light reflect & surface to cam vector, uses dot product 
 * of halfway vector & surface normal, which is cheaper to compute.
 * From: https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model &
 * https://www.youtube.com/watch?v=KdDdljGtfeg
 */
t_vec4f	blinn_phong_shading(t_scene_data *scene, t_hit_info surface)
{
	const t_vec4f	surface_to_light = scene->light.location - surface.hit_location;
	const t_vec4f	surface_to_cam = scene->camera.location - surface.hit_location;
	const float		distance_to_light = vector_length(surface_to_light);
	const float		distance_to_cam = vector_length(surface_to_cam);
	const float		strength = scene->light.ratio / distance_to_light * 50.0f;
	t_vec4f			halfway_vec = (surface_to_light + surface_to_cam) / (distance_to_light + distance_to_cam); // wat doet de / (dist1 + dist2)  als je toch gaat normalizen?
	t_vec4f			diffuse;
	t_vec4f			specular;
	t_vec4f			ambient;
	const int		fac = 128;

	normalize_vector(&halfway_vec);
	ambient = (scene->ambient.ratio * scene->ambient.color.rgb_f + scene->ambient.ratio * surface.material.color) / 2;
	diffuse = ft_maxf(dot_product_3d(surface_to_light, surface.normal) / distance_to_light, 0.0f) * surface.material.color;
	const float spec_strength = 0.5f;
	specular = powf(ft_maxf(dot_product_3d(halfway_vec, surface.normal), 0.0f), fac) * scene->light.color.rgb_f * spec_strength;
	surface.material.color = (diffuse + specular) * strength + ambient;// hoe is de voorrang van haakjes?
	surface.material.color[0] = ft_min(surface.material.color[0], 255);
	surface.material.color[1] = ft_min(surface.material.color[1], 255);
	surface.material.color[2] = ft_min(surface.material.color[2], 255);// kleuren tussen float 0 - 255 ?
	return (surface.material.color);
}

void	update_hit_info(t_hit_info *hit_info, t_vec4f hit, t_object *object, \
						float length)
{
	hit_info->hit_location = hit;
	hit_info->object = object;
	hit_info->length = length;
	hit_info->material.color = object->get_color(object->object);
	hit_info->material.smoothness = object->get_smoothness(object->object);
	// if (hit_info->material.smoothness > 0)
	// 	printf("smoothness %f\n", hit_info->material.smoothness);
	t_vec4f obj_center = object->get_location(object->object);
	hit_info->normal = hit - object->get_location(object->object);
	normalize_vector(&hit_info->normal);
}

#define STATUS_INDEX 3

t_vec4f lerp(t_vec4f a, t_vec4f b, float f) 
{
    return (a * (float)(1.0 - f)) + (b * f);
}

t_vec4f	sky_box(float y)
{
	t_vec4f	color1 = (t_vec4f){145,224,255,1};
	t_vec4f	color2 = (t_vec4f){255,255,255,1};

	return (lerp(color2, color1, (y + 1.0f) / 2));
}

/**
 * @note Keeps track of closest intersection object.
 * bg_strength is used for the effect of the ambient color strength 
 * on the background, so it is different from the object's "shadow" color.
 * 
 * 
 * 	0.0 smoothness means * 1
 *  1.0 smoothness means * 0
 */
t_vec4f	object_hit_color(t_scene_data *scene, t_ray ray, t_hit_info	*closest_hit)
{
	t_object	*current;
	//t_hit_info	closest_hit;//move
	t_vec4f		hit;
	float		length;
	const float	bg_strength = 0.2f;

	current = scene->objects;
	closest_hit->hit_location = (t_vec4f){0, 0, 0, -1};
	closest_hit->length = 200;
	while (current)
	{
		hit = current->intersect(current->object, ray);
		if (hit[STATUS_INDEX] != -1)
		{
			length = fabsf(vector_length(hit - ray.origin)); // fabs omdat we ook in de negatieve richting kunnen kijken als de camera zo staat?
			if (length <= closest_hit->length)
				update_hit_info(closest_hit, hit, current, length);
		}
		current = current->next;
	}
	if (closest_hit->hit_location[STATUS_INDEX] == -1)
		return (sky_box(ray.direction[2]));
	return (blinn_phong_shading(scene, *closest_hit) * (1 - closest_hit->material.smoothness));
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

t_vec4f reflect(t_vec4f normal, t_vec4f incoming)
{
	t_vec4f reflection;

	reflection = incoming - (2 * dot_product_3d(incoming, normal) * normal);
	return reflection;
}

#define MAX_BOUNCE_DEPTH 2
#define REFLECT_RAYS 5

t_vec4f	trace_ray(t_scene_data *scene, t_ray ray, int bounce_depth)
{
	int i;
	t_vec4f this_color;
	t_vec4f color_bounce_sum = (t_vec4f){0,0,0,0};
	t_hit_info hit_info;

	i = 0;
	this_color = object_hit_color(scene, ray, &hit_info);
	// if (bounce_depth != 0)
	// 	this_color *= fminf(1.0f, 5.0f / hit_info.length);
	if (this_color[STATUS_INDEX] == -1)
		return this_color; //zit in de lucht
	if (bounce_depth == MAX_BOUNCE_DEPTH)
		return this_color;
	ray.origin = hit_info.hit_location;
	while (i < REFLECT_RAYS)
	{
		t_vec4f diffuse_ray = generate_random_vec4f();
		t_vec4f reflection = reflect(hit_info.normal, ray.direction);//using old direction

		if (dot_product_3d(hit_info.normal, diffuse_ray) < 0)
			diffuse_ray *= -1;
		ray.direction = lerp(diffuse_ray, reflection, hit_info.material.smoothness);
		// printf("reflectiveness %f\n", dot_product_3d(reflection, ray.direction));
		color_bounce_sum += trace_ray(scene, ray, bounce_depth + 1);
		i++;
	}
	// this_color *=
	color_bounce_sum /= REFLECT_RAYS;
	// this_color *= 2; //telt 3/4 keer mee en reflecties 1/4
	return ((this_color + color_bounce_sum) / 2 );// heb geen idee hoe het echt moet
	//hoeveel this_color meetelt te maken met hoeveel licht wordt geabsorbeerd?
	//als al het licht wordt geabsorbeerd, geen specular en geen reflections
	//
}


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
	const float	inc = 2 * M_PI / samples;

	angle = 0;
	i = 0;
	color = (t_vec4f){0, 0, 0, -1};
	ray = construct_camera_ray(raycenter[0], raycenter[1], scene, aspect_ratio);
	color = trace_ray(scene, ray, 0);
	return color;
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