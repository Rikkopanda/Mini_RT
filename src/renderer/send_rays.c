/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/06/11 13:06:22 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * make factor fall between 0 and 1
*/
void fit_interpolation_range(float *rgb_factor)
{
	*rgb_factor += 1;
	*rgb_factor *= 0.5;
}

int visualize_sphere_normals(t_scene_data *data, t_vec4f res_xyz)
{
	t_vec4f rgb_factor;
	(void)data;
	normalize_vector(res_xyz);
	copy_matrix(rgb_factor, res_xyz);
	fit_interpolation_range(&rgb_factor[0]);
	fit_interpolation_range(&rgb_factor[1]);
	fit_interpolation_range(&rgb_factor[2]);
	// printf("factor\n");
	// print_matrix_1_3(rgb_factor);
	// printf("________________________\n");
	// return (create_color(interpolate(BLUE, ORANGE, rgb_factor[0]) << 16, interpolate(RED, WHITE, rgb_factor[1]) << 8, interpolate(GREEN, BLACK, rgb_factor[2])));
	int const color1 = interpolate(BLUE, (int)WHITE, rgb_factor[0]);
	int const color2 = interpolate(RED, color1, rgb_factor[1]);
	int const color3 = interpolate(GREEN, color2, rgb_factor[2]);

	return (color3);
	// return (interpolate(BLUE, ORANGE, rgb_factor[0]));
	// return (create_color((int)((float)255 * rgb_factor[0]) & 0xFF, (int)((float)255 * rgb_factor[1]) & 0xFF, (int)((float)255 * rgb_factor[2]) & 0xFF));
}

/**
 * vector from point A to point B
*/
t_vec4f	points_derived_vector(t_vec4f point_A, t_vec4f point_B)
{
	t_vec4f	result_vec;

	result_vec[0] = point_B[0] - point_A[0]; 
 	result_vec[1] = point_B[1] - point_A[1];  
	result_vec[2] = point_B[2] - point_A[2];  
	return (result_vec);
}

void moved_vector_position(t_vec4f result, t_vec4f target_vec, t_vec4f offset)
{
	result[0] = target_vec[0] - offset[0]; 
 	result[1] = target_vec[1] - offset[1];  
	result[2] = target_vec[2] - offset[2];
}

int	sphere_intersection_equation(t_scene_data *data, t_vec4f obj_to_ray_vec)
{
	const float squared = powf(obj_to_ray_vec[0], 2) + powf(obj_to_ray_vec[1], 2) + powf(obj_to_ray_vec[2], 2);

	if (sqrtf(squared) <= data->sphere.radius)
		return (TRUE);
	else
		return (FALSE);
}

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

/**
 * @note not declaring and initializing new vectors faster??
*/
int check_if_hit(t_scene_data *data, t_ray *ray, t_vec4f *obj_to_ray_vec)
{
	moved_vector_position(ray->world_pos_of_scaled_vec, ray->scaled_vec, data->camera.location);
	// print_matrix_1_3(ray->world_pos_of_scaled_vec);
	
	*obj_to_ray_vec = points_derived_vector(data->sphere.location, ray->world_pos_of_scaled_vec);
	// printf("ray scaled\n"); 
	// print_matrix_1_3(ray->scaled_vec);
	// printf("obj to ray vec\n");
	// print_matrix_1_3(obj_to_ray_vec);
	// sleep(1);
	if (sphere_intersection_equation(data, *obj_to_ray_vec) == TRUE)
	{
		// visualize_sphere_normals(data, res_xyz);
		// return (visualize_sphere_normals(data, (*obj_to_ray_vec)));
		// int shadow_check = shadow_ray_to_light();
		// return ();
		return (data->sphere.hexcolor);
	}
	else
		return ((int)NADA);
	// usleep(5000);
	// printf("result xyz %f %f %f\n", res_xyz[0], res_xyz[1], res_xyz[2]);
	// printf("sqrt(squared) %f\n", sqrt(squared));
	// printf("radius %f\n",  data->sphere.radius);
	// sleep(1);
}

int	shadow_ray_to_light(t_scene_data *data)
{

	t_vec4f	position[3];
	t_vec4f	light_ray[3];

// 	int steps = 0;

// 	position[0] = surface_point[0] + light_ray[0];
// 	position[1] = surface_point[1] + light_ray[1];
// 	position[2] = surface_point[2] + light_ray[2];
// 	while (steps < 200) // ray in object? = shadow
// 	{
// 		position[0] += light_ray[0];
// 		position[1] += light_ray[1];
// 		position[2] += light_ray[2];
// 		// if (PRINT_DEBUG) print_matrix_1_3(position);
// 		if (check_if_hit(data, position))
// 			return (FALSE);
// 		steps++;
// 	}
	return (TRUE);
}

void	increment_vec4f(t_vec4f *scaled_vector, t_vec4f *normalize_vector)
{
	(*scaled_vector)[0] += (*normalize_vector)[0];
	(*scaled_vector)[1] += (*normalize_vector)[1];
	(*scaled_vector)[2] += (*normalize_vector)[2];
}

// float	*int_1x3_to_float_1x3(int i_arr[3])
// {
// 	float	f_arr[3];
// 	int		i;

// 	i = 0;	
// 	while (i < 3)
// 	{
// 		f_arr[i] = i_arr[i];
// 		i++;
// 	}
// 	return (f_arr);
// }


int	hit_ray(t_scene_data *data, float angle_horiz, float angle_vert)
{
	t_vec4f	rota_horiz[3];
	t_vec4f	rota_vert[3];
	t_vec4f	comp[3];

	init_t_around_z(rota_horiz, angle_horiz);
	init_t_around_y(rota_vert, angle_vert);
	compilation_matrix(comp, rota_horiz, rota_vert);

	// if (PRINT_DEBUG) printf("angles horizontal, vertical: %f\t%f\n", ft_rad_to_degr(angle_horiz), ft_rad_to_degr(angle_vert));
	// if (PRINT_DEBUG) printf("_________________\n");
	// if (PRINT_DEBUG) printf("rotation\n");
	// if (PRINT_DEBUG) print_matrix_3_3(comp);
	// if (PRINT_DEBUG) printf("original\n");
	// if (PRINT_DEBUG) print_matrix_1_3(data->camera.view_orientation_matrix);

	init_result(data->ray.normalized_vec);

	matrix_multiply_1x3_3x3(data->camera.orientation, comp, data->ray.normalized_vec);

	// if (PRINT_DEBUG) printf("result:\n");
	// if (PRINT_DEBUG) print_matrix_1_3(data->ray.normalized_vec);
	// if (PRINT_DEBUG) printf("_________________\n\n");
	// sleep(2);
	data->ray.step = 1;
	init_result(data->ray.scaled_vec);

	while (data->ray.step < 200)
	{
		int resulting_color;

		t_vec4f			obj_to_ray_vec;
		// sleep(1);
		t_color color;

		increment_vec4f(&data->ray.scaled_vec, &data->ray.normalized_vec);
		color.color_code = check_if_hit(data, &data->ray, &obj_to_ray_vec);
		// if (dot_product_3d())
		if (color.color_code != NADA)
		{
			t_vec4f surface_normal;
			
			copy_matrix(surface_normal, obj_to_ray_vec);
			normalize_vector(surface_normal);
			t_vec4f	*surface_point = &data->ray.scaled_vec;// must be actual surface point, not in the object! like now
			// print_matrix_1_3(data->ray.scaled_vec);
			// print_matrix_1_3(data->light.position);

			t_vec4f surface_to_light_ray = points_derived_vector(data->ray.scaled_vec, data->light.location);
			normalize_vector(surface_to_light_ray);
			// printf("surface normal:\n");
			// print_matrix_1_3(surface_normal);
			// printf("surface to light:\n");
			// print_matrix_1_3(surface_to_light_ray);
			// printf(" ______:\n");
			// sleep(1);
			// float one[3] = {-200, -200, -100};
			// float two[3] = {-100, -100, -100};

			// normalize_vector(one);
			// normalize_vector(two);

			// printf("dot product %f\n_______\n", dot_product_3d(one, two));
			float rgb_factor = dot_product_3d(surface_normal, surface_to_light_ray);
			if (rgb_factor <= 0)
				return (GREEN);
			init_rgb(&color, data->sphere.hexcolor);
			init_rgb_f(color.rgb_f, color.rgb);
			normalize_vector(color.rgb_f);
			vector_scaling(color.rgb_f, rgb_factor);
			make_rgb_with_normalized_rgb_f(color.rgb, color.rgb_f);
			color.color_code = create_color(color.rgb[0], color.rgb[1], color.rgb[2]);
			// printf("dot product %f\n", dot_product_3d(surface_normal, surface_to_light_ray));
			return (color.color_code);
		}
		data->ray.step += 1;
		// if (PRINT_DEBUG) print_matrix_1_3(data->ray.scaled_vec);
	}
	// if (angle_horiz > 0 && angle_horiz < 0.09)
	// 	printf("%f\n", data->ray.direction_abc[2]);
	return (NADA);
}

// int	world_horizon_opposed_to_ray(t_scene_data *data)
// {
// }

void send_rays(t_scene_data *scene)
{
	t_ray_sending_tools	r_t;
	int					color;

	init_ray_send_tools(&r_t, scene);
	r_t.pixel_y = 0;
	while (r_t.pixel_y <= WINDOW_HEIGHT)
	{
		r_t.pixel_x = 0;
		r_t.angle_vert = atan2(r_t.half_screen_height - r_t.pixel_y, r_t.perpendicular_distance_vert_triangle);
		while (r_t.pixel_x <= WINDOW_WIDTH)
		{
			r_t.angle_horiz = atan2(-r_t.half_screen_width + r_t.pixel_x, r_t.perpendicular_distance_horiz_triangle);
			color = NADA;
			color = hit_ray(scene, r_t.angle_horiz, r_t.angle_vert);
			if (color == NADA)
			{
				float unit_point;
				// unit_point = world_horizon_opposed_to_ray(data);
				unit_point = (r_t.angle_vert - r_t.start_angle_vert) / ft_degr_to_rad((float)scene->camera.fov);
				color = interpolate(WHITE, BLUE, unit_point);
			}
			// printf("%p", (void *)&scene->image);
			// exit(0);
			put_pixel_img(scene->image, r_t.pixel_x, r_t.pixel_y, color);
			r_t.pixel_x++;
		}
		r_t.pixel_y++;
	}
}
/*
clock_t				t;
t = clock();
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
printf("The program took %f seconds to execute\n", time_taken);
printf("done\n");

// if (PRINT_DEBUG) printf("angles horizontal, vertical: 1  %f\t%f\n", ft_rad_to_degr(r_t.angle_horiz), ft_rad_to_degr(r_t.angle_vert));
// printf("perp hori %f\n", r_t.perpendicular_distance_horiz_triangle);
// printf("perp verti %f\n", r_t.perpendicular_distance_vert_triangle);
// printf("screen half %d\n, ", r_t.half_screen_width);
// sleep(1);
*/