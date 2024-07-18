/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/07/18 14:20:58 by rverhoev         ###   ########.fr       */
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

int visualize_sphere_normals(t_scene_data *data, t_vec4f res_xyz)
{
	t_vec4f rgb_factor;
	(void)data;
	normalize_vector(&res_xyz);
	// copy_matrix(&rgb_factor, res_xyz);
	rgb_factor = res_xyz;
	// fit_interpolation_range(&rgb_factor[0]);
	// fit_interpolation_range(&rgb_factor[1]);
	// fit_interpolation_range(&rgb_factor[2]);
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

	result_vec = point_B - point_A;   
	return (result_vec);
}

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

float	cross_product_3d(t_vec4f vec_A, t_vec4f vec_B)
{
	return ((vec_A[2] * vec_B[3]) - (vec_B[2] * vec_A[3]) +
			(vec_A[3] * vec_B[1]) - (vec_B[3] * vec_A[1]) +
			(vec_A[1] * vec_B[2]) - (vec_B[1] * vec_A[2]));
}

/**
 * @note not declaring and initializing new vectors faster??
*/
t_vec4f check_if_hit(t_scene_data *data, t_ray *ray, t_hit_data *hit_data)
{
	t_object	*current;
	t_vec4f		hit;

	// printf("sphere.location\n");
	// print_matrix_1_3(data->sphere.location);
	// moved_vector_position(&ray->world_pos_of_scaled_vec, ray->scaled_vec, data->camera.location);

	// printf("world_pos_of_scaled_vec\n");
	// print_matrix_1_3(ray->world_pos_of_scaled_vec);
	// printf("sphere.location\n");
	// print_matrix_1_3(data->sphere.location);

	// printf("ray scaled\n"); 
	// print_matrix_1_3(ray->scaled_vec);
	// sleep(1);
	// while ()

	current = data->objects;
	while (current != NULL)
	{
		// print_camera_data(data->camera);
		// printf("data camera: x, y, z %f %f %f\n", data->camera.location[0], data->camera.location[1], data->camera.location[2]);

		// printf("hallo\n");
		// current->print_object_data(current->object);
		// *obj_to_ray_vec = points_derived_vector(current->get_location(current->object), ray->world_pos_of_scaled_vec);
		hit = current->intersect(current->object, *ray);
		hit_data->surface_normal = hit - current->get_location(current);
		normalize_vector(&hit_data->surface_normal);
		if (hit[3] != -1)
		{
			// print_matrix_1_3(hit);
			// printf("\t%f", hit[3]);
			hit_data->color.color_code = current->get_color(current);
			printf("\ncolor code %d \n\n", hit_data->color.color_code);

			return (hit);
		}
		current = current->next;
	}
	return (hit);
}

int	shadow_ray_to_light(t_scene_data *data)
{

	// t_vec4f	position[3];
	// t_vec4f	light_ray[3];
	(void)data;
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
	(*scaled_vector) += (*normalize_vector);
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

int	hit_ray(t_scene_data *data)
{
	// data->ray.normalized_vec = new_dir_method_ray_test;
	normalize_vector(&data->ray.normalized_vec);
	// if (PRINT_DEBUG) printf("new result:\n");
	// if (PRINT_DEBUG) print_matrix_1_3(data->ray.normalized_vec);
	// if (PRINT_DEBUG) printf("_________________\n\n");

	// int		resulting_color;
	t_vec4f	obj_to_ray_vec;
	t_hit_data hit_data;
	// increment_vec4f(&data->ray.scaled_vec, &data->ray.normalized_vec);
	init_result(&obj_to_ray_vec);
	init_result(&hit_data.color.rgb_f);

	t_vec4f hit = check_if_hit(data, &data->ray, &hit_data);
	// printf("ptr:1 %p\n", &obj_to_ray_vec);
	// printf("color code: %d\n", color.color_code);

	if (hit[3] != NADA)
	{
		printf("color code: %d\n", hit_data.color.color_code);


		// printf("____________________\n scaled HIT: ");
		// if (PRINT_DEBUG) print_matrix_1_3(data->ray.scaled_vec);
		// print_matrix_1_3(surface_normal);
		// normalize_vector(&surface_normal);
		// t_vec4f	*surface_point = &data->ray.scaled_vec;// must be actual surface point, not in the object! like now
		// printf("color code: %d\n", color.color_code);

		t_vec4f surface_to_light_ray = points_derived_vector(hit, data->light.location);
		// printf(" DEZE color code: %d\n", color.color_code);
		normalize_vector(&surface_to_light_ray);
		// printf(" DIE color code: %d\n", color.color_code);
		float rgb_factor = dot_product_3d(hit_data.surface_normal, surface_to_light_ray);
		// printf("%f\n", rgb_factor);

		if (rgb_factor <= 0)
		{
			return (BLACK);
		}
		// if (rgb_factor > 0.2)
		// 	printf("black after: %f\n", rgb_factor);
		// printf("color code: %d\n", color.color_code);

		init_rgb(&hit_data.color, hit_data.color.color_code);
		
		printf("bug gespot: %d -> %d %d %d\n", hit_data.color.color_code, hit_data.color.rgb[0], hit_data.color.rgb[1], hit_data.color.rgb[2]);
		
		init_rgb_f(&hit_data.color.rgb_f, hit_data.color.rgb);
		normalize_vector(&hit_data.color.rgb_f);
		vector_scaling(&hit_data.color.rgb_f, rgb_factor);
		make_rgb_with_normalized_rgb_f(hit_data.color.rgb, hit_data.color.rgb_f);
		hit_data.color.color_code = create_color(hit_data.color.rgb[0], hit_data.color.rgb[1], hit_data.color.rgb[2]);
		return (hit_data.color.color_code);
	}
	
	// if (angle_horiz > 0 && angle_horiz < 0.09)
	// 	printf("%f\n", data->ray.direction_abc[2]);
	return (NADA);
}
/*
		print_matrix_1_3(data->ray.scaled_vec);

		printf("dot product %f\n", dot_product_3d(surface_normal, surface_to_light_ray));
		// print_matrix_1_3(data->ray.scaled_vec);
		// print_matrix_1_3(data->light.position);

	printf("surface normal:\n");
	print_matrix_1_3(surface_normal);
	printf(" ______:\n");
	sleep(1);
	float one[3] = {-200, -200, -100};
	float two[3] = {-100, -100, -100};

	normalize_vector(one);
	normalize_vector(two);

	printf("dot product %f\n_______\n", dot_product_3d(one, two));

*/

// int	world_horizon_opposed_to_ray(t_scene_data *data)
// {
// }

void send_rays(t_scene_data *scene)
{
	t_ray_sending_tools	r_t;
	int					color;
	const float aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH; j++)
		{
			put_pixel_img(scene->image, i, j, BLACK);
		}
	}
	init_ray_send_tools(&r_t, scene);
	r_t.pixel_y = 0;
	while (r_t.pixel_y <= WINDOW_HEIGHT)
	{
		r_t.pixel_x = 0;
		// printf("left\n");
		while (r_t.pixel_x <= WINDOW_WIDTH)
		{

			float pixelNDCx = ((float)r_t.pixel_x + (float)0.5) / (float)WINDOW_WIDTH;
			// + 0.5 because it has to be in the middle of the pixel(raster square, how u want to call it)
			float pixelNDCy = ((float)r_t.pixel_y + (float)0.5) / (float)WINDOW_HEIGHT;
			// printf("NDC space x y %f\t%f\n", pixelNDCx, pixelNDCy);

			float scale = tanf(ft_degr_to_rad(scene->camera.fov) * 0.5);
			float pixel_screen_x = ((2 * pixelNDCx) - 1) * aspect_ratio * scale;
			float pixel_screen_y = (1 - (2 * pixelNDCy)) * scale;
			
			// float pixel_screen_x =  pixelNDCx * aspect_ratio;
			// float pixel_screen_y =  pixelNDCy;
			// printf("angles horizontal, vertical:  %f\t%f\n", ft_rad_to_degr(r_t.angle_horiz), ft_rad_to_degr(r_t.angle_vert));

			// printf("screen space x y %f\t%f\n\n", pixel_screen_x, pixel_screen_y);
			// float pixel_angle_screen_space_x = atanf(pixel_screen_x / 1);
			// float pixel_angle_screen_space_y = atanf(pixel_screen_y / 1);
			// float pixel_angle_screen_space_x = tanf(ft_degr_to_rad(scene->camera.fov) * 0.5);
			// float pixel_angle_screen_space_y = tanf(ft_degr_to_rad(scene->camera.fov) * 0.5);
			// printf("angle pixel camara space along x, y; %f\t%f\n\n", ft_rad_to_degr(pixel_angle_screen_space_x), ft_rad_to_degr(pixel_angle_screen_space_y));

			// float pixel_camara_x = pixel_screen_x * tanf(pixel_angle_screen_space_x);
			// float pixel_camara_y = pixel_screen_y * tanf(pixel_angle_screen_space_y);

			t_vec4f	rota_horiz[3];
			t_vec4f	rota_vert[3];
			t_vec4f	comp[3];
			t_vec4f	comp2[3];
			t_vec4f	comp3[3];
			// if (PRINT_DEBUG) printf("angles horizontal, vertical: %f\t%f\n", ft_rad_to_degr(pixel_angle_screen_space_x), ft_rad_to_degr(pixel_angle_screen_space_y));
			
			init_t_around_z(rota_horiz, DEGR_10_IN_RAD * 2);

			// init_t_around_z(rota_horiz, pixel_angle_screen_space_x);
			// rota_horiz[0] += scene->camera.rotation_around_z[0];
			// rota_horiz[1] += scene->camera.rotation_around_z[1];
			// rota_horiz[2] += scene->camera.rotation_around_z[2];
			// init_t_around_y(rota_vert, pixel_angle_screen_space_y);

			// matrix_multiply_3x3_3x3(rota_horiz, rota_vert, comp);

			matrix_multiply_3x3_3x3(scene->camera.rotation_comp, rota_horiz, comp2); // rota_comp either be identity(no change), or adjusted by hook

			// if (PRINT_DEBUG && r_t.pixel_x == 0 && r_t.pixel_y == WINDOW_HEIGHT / 2) print_matrix_3_3(comp);
			
			// if (PRINT_DEBUG && r_t.pixel_x == 0 && r_t.pixel_y == WINDOW_HEIGHT / 2) printf("VERSCHIL\n");

			// if (PRINT_DEBUG && r_t.pixel_x == 0 && r_t.pixel_y == WINDOW_HEIGHT / 2) print_matrix_3_3(comp2);

			// exit(0);
			// init_t_around_z(rota_horiz, DEGR_10_IN_RAD * 5);
			// init_t_around_y(rota_vert, 0);
			// init_identy_matrix(comp2);
			// matrix_multiply_3x3_3x3(comp2, rota_horiz, rota_vert);
			// init_identy_matrix(comp3);
			// matrix_multiply_3x3_3x3(comp2, comp, comp3);

			// if (PRINT_DEBUG) printf("angles horizontal, vertical: %f\t%f\n", ft_rad_to_degr(angle_horiz), ft_rad_to_degr(angle_vert));
			// if (PRINT_DEBUG) printf("_________________\n");
			// if (PRINT_DEBUG) printf("rotation\n");
			// if (PRINT_DEBUG) print_matrix_3_3(comp);
			// if (PRINT_DEBUG) printf("original\n");
			// if (PRINT_DEBUG) print_matrix_1_3(scene->camera.orientation);

			// init_result(&data->ray.normalized_vec);
			// t_vec4f camara_space_vec = t_vec4f_construct(1, pixel_screen_y, pixel_screen_x * -1);
			scene->ray.normalized_vec = (t_vec4f){0, 0, 0, 0};

			// matrix_multiply_1x3_3x3(&scene->camera.orientation, comp2, &scene->ray.normalized_vec);

			// if (PRINT_DEBUG) print_matrix_1_3(scene->ray.normalized_vec);

			t_vec4f camara_space_vec = t_vec4f_construct(1, pixel_screen_x, pixel_screen_y * -1);
			// scene->ray.normalized_vec = (t_vec4f){0, 0, 0, 0};
			// scene->ray.normalized_vec = camara_space_vec;
			matrix_multiply_1x3_3x3(&camara_space_vec, comp2, &scene->ray.normalized_vec);

			// matrix_multiply_1x3_3x3(&scene->camera.orientation, comp3, &scene->ray.normalized_vec);

			// scene->ray.normalized_vec[1] += 1;
			// scene->ray.normalized_vec[1] /= 2;
			// scene->ray.normalized_vec[2] += 1;
			// scene->ray.normalized_vec[2] /= 2;
			// int test_pixel_x = (int)((float)scene->ray.normalized_vec[1] * (float)WINDOW_WIDTH);
			// int test_pixel_y = (int)((float)scene->ray.normalized_vec[2] * (float)WINDOW_HEIGHT);

			// put_pixel_img(scene->image, test_pixel_x, test_pixel_y, BLUE);

			// printf("camera space(3d) x y z %f\t%f\t%f\n\n", ray.normalized_vec[0], ray.normalized_vec[1], ray.normalized_vec[2]);
			// sleep(1);
			color = hit_ray(scene);//0.386221	-0.837061	-0.387509
			//0.565031	-0.599457	-0.566914	

			if (color == NADA)
			{
				float unit_point;
				// unit_point = world_horizon_opposed_to_ray(data);
				unit_point = r_t.pixel_y / (float)WINDOW_HEIGHT;
				color = interpolate(GREEN, BLUE, unit_point);
				// put_pixel_img(scene->image, r_t.pixel_x, r_t.pixel_y, color);
			}
			put_pixel_img(scene->image, r_t.pixel_x, r_t.pixel_y, color);
			// printf("right\n");

			// if (r_t.pixel_x == WINDOW_WIDTH && r_t.pixel_y == WINDOW_HEIGHT / 2) print_matrix_1_3(scene->ray.normalized_vec);

			r_t.pixel_x++;
		}
		r_t.pixel_y++;
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