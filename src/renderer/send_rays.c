/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:18:38 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/07/25 13:41:11 by rverhoev         ###   ########.fr       */
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

/**
 * @note not declaring and initializing new vectors faster??
*/
t_vec4f check_if_hit(t_scene_data *data, t_ray *ray, t_hit_data *hit_data)
{
	t_object	*current;
	t_vec4f		hit;

	current = data->objects;
	while (current != NULL)
	{
		hit = current->intersect(current->object, *ray);
		if (hit[3] != -1)
		{
			t_vec4f obj_location = current->get_location(current->object);
			hit_data->surface_normal = hit - obj_location;
			// printf("\nLOCATION OBJ, NORMAL , HITSURFACE\n");
			// print_matrix_1_3(obj_location);
			// print_matrix_1_3(hit);
			// print_matrix_1_3(hit_data->surface_normal);
			normalize_vector(&hit_data->surface_normal);
			// print_matrix_1_3(hit_data->surface_normal);

			hit_data->color.color_code = current->get_color(current->object);
			init_result(&hit_data->color.rgb_f);
			init_rgb(&hit_data->color, hit_data->color.color_code);
			init_rgb_f(&hit_data->color.rgb_f, hit_data->color.rgb);
			normalize_vector(&hit_data->color.rgb_f);

			// printf("\ncolor code %d \n\n", hit_data->color.color_code);
			return (hit);
		}
		current = current->next;
	}
	return (hit);
}
// print_camera_data(data->camera);
// printf("data camera: x, y, z %f %f %f\n", data->camera.location[0], data->camera.location[1], data->camera.location[2]);
// printf("hallo\n");
// current->print_object_data(current->object);
// *obj_to_ray_vec = points_derived_vector(current->get_location(current->object), ray->world_pos_of_scaled_vec);

int	hit_ray(t_scene_data *data)
{
	t_hit_data hit_data;

	normalize_vector(&data->ray.normalized_vec);
	t_vec4f hit = check_if_hit(data, &data->ray, &hit_data);
	if (hit[3] != NADA)
	{
		t_vec4f surface_to_light_ray = data->light.location - hit;

		normalize_vector(&surface_to_light_ray);

		// print_matrix_1_3(hit);
		t_vec4f_color light_color = (t_vec4f_color){1, 1, 1, 1};
		t_vec4f_color ambient = (t_vec4f_color){0.2, 0.2, 0.2, 1};
		float diffuse_strenght = fmaxf(0.0, dot_product_3d(hit_data.surface_normal, surface_to_light_ray));

		// printf("surface to light:\n");
		// print_matrix_1_3(surface_to_light_ray);
		// printf("surface_normal:\n");
		// print_matrix_1_3(hit_data.surface_normal);

		t_vec4f_color diffuse = light_color * diffuse_strenght;
		t_vec4f view_src = data->camera.location - hit;
		normalize_vector(&view_src);

		t_vec4f half_way = (view_src + surface_to_light_ray) / (get_magnitude(surface_to_light_ray) + get_magnitude(view_src));
		normalize_vector(&half_way);

		float specular_strenght = fmaxf(0.0f, dot_product_3d(hit_data.surface_normal, half_way));

		specular_strenght = powf(specular_strenght, 32);
		t_vec4f_color specular = specular_strenght * light_color;

		ambient *= hit_data.color.rgb_f;
		diffuse *= hit_data.color.rgb_f;

		t_vec4f_color lightning_result = ((ambient * (float)0.2) + (diffuse * (float)0) + (specular * (float)1));
		// hit_data.color.rgb_f = hit_data.color.rgb_f * lightning_result;
		
		make_rgb_with_normalized_rgb_f(hit_data.color.rgb, lightning_result);
		hit_data.color.color_code = create_color(hit_data.color.rgb[0], hit_data.color.rgb[1], hit_data.color.rgb[2]);
		return (hit_data.color.color_code);
	}
	return (NADA);
}
/*

		
		// printf("bug gespot: %d -> %d %d %d\n", hit_data.color.color_code, hit_data.color.rgb[0], hit_data.color.rgb[1], hit_data.color.rgb[2]);
		// print_matrix_1_3(surface_to_light_ray);
		// print_matrix_1_3(half_way);
		// print_matrix_1_3(view_src);
		// printf("\n\n");
		// printf("%f\n", specular_strenght);
		// exit(0);
		// specular_strenght = powf(specular_strenght, 4);
		// printf("%f\n", specular_strenght);

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

t_vec4f make_camera_space_vector(t_scene_data *scene, t_ray_sending_tools *r_t)
{
	const float aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

	float pixelNDCx = ((float)r_t->pixel_x + (float)0.5) / (float)WINDOW_WIDTH;
	// + 0.5 because it has to be in the middle of the pixel(raster square, how u want to call it)
	float pixelNDCy = ((float)r_t->pixel_y + (float)0.5) / (float)WINDOW_HEIGHT;
	// printf("NDC space x y %f\t%f\n", pixelNDCx, pixelNDCy);

	float scale = tanf(ft_degr_to_rad(scene->camera.fov) * 0.5);
	float pixel_screen_x = ((2 * pixelNDCx) - 1) * aspect_ratio * scale;
	float pixel_screen_y = (1 - (2 * pixelNDCy)) * scale;

	return t_vec4f_construct(1, pixel_screen_x, pixel_screen_y);// dir: x y z
}

void send_rays(t_scene_data *scene)
{
	t_ray_sending_tools	r_t;
	int					color;
	scene->ray.origin = scene->camera.location;

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
		while (r_t.pixel_x <= WINDOW_WIDTH)
		{
			t_vec4f camara_space_vec = make_camera_space_vector(scene, &r_t);
			matrix_multiply_1x3_3x3(&camara_space_vec, scene->camera.rotation_comp, &scene->ray.normalized_vec);
			#ifdef PRINT_DEBUG
				printf("user input orientation\n");
				print_matrix_1_3(scene->camera.orientation);
				printf("reference vector\n");
				const t_vec4f reference_vector = {1,0,0,1};
				print_matrix_1_3(reference_vector);
				printf("camera space\n");
				print_matrix_1_3(camara_space_vec);
				printf("rotation\n");
				print_matrix_3_3(scene->camera.rotation_comp);
				printf("original\n");
				print_matrix_1_3(scene->ray.normalized_vec);
				printf("\n\ncalculation\n");
				printf("\n\ncross\n");

				t_vec4f cross_vector = cross_product(reference_vector, scene->camera.orientation);
				normalize_vector(&cross_vector);
				print_matrix_1_3(cross_vector);

				float angle = acosf(dot_product_3d(reference_vector, scene->camera.orientation) / (get_magnitude(reference_vector) * get_magnitude(scene->camera.orientation)));
				printf("angle\n%f\n", angle);

				t_vec4f K[3] = {(t_vec4f){0, -cross_vector[2], cross_vector[1]},
							(t_vec4f){cross_vector[2], 0, -cross_vector[0]},
							(t_vec4f){-cross_vector[1], cross_vector[0], 0}};
				printf("K\n");
				print_matrix_3_3(K);

				t_vec4f I[3];
				t_vec4f R[3];
				init_identy_matrix(I);
				copy_matrix(R, I);

				t_vec4f K_sin_theta[3];
				copy_matrix(K_sin_theta, K);
				scale_3x3_matrix(K_sin_theta, sinf(angle));
				printf("K scale  sin(theta)\n");
				print_matrix_3_3(K_sin_theta);
				t_vec4f K_squared_and_cos[3];
				matrix_multiply_3x3_3x3(K, K, K_squared_and_cos);
				scale_3x3_matrix(K_squared_and_cos, 1 - cosf(angle));
				printf("K squared and cos theta\n");

				print_matrix_3_3(K_squared_and_cos);
				printf("R add 1\n");

				matrix_addition(R, K_sin_theta);
				print_matrix_3_3(R);

				matrix_addition(R, K_squared_and_cos);
				printf("R add 2\n");
				print_matrix_3_3(R);

				t_vec4f test_result;
				matrix_multiply_1x3_3x3((t_vec4f *)&scene->camera.orientation, R, &test_result);
				printf("camera orientation x R =\n");
				print_matrix_1_3(test_result);
			
				matrix_multiply_1x3_3x3((t_vec4f *)&reference_vector, R, &test_result);
				printf("ref x R =\n");
				print_matrix_1_3(test_result);

				printf("camera space vector pre\n");
				print_matrix_1_3(camara_space_vec);
				matrix_multiply_1x3_3x3((t_vec4f *)&camara_space_vec, R, &test_result);
				printf("camera space vector multiplied by R\n");
				print_matrix_1_3(test_result);
				// exit(0);
			#endif
			color = hit_ray(scene);//0.386221	-0.837061	-0.387509
			if (color == NADA)
			{
				float unit_point;
				// unit_point = world_horizon_opposed_to_ray(data);
				unit_point = r_t.pixel_y / (float)WINDOW_HEIGHT;
				color = interpolate(GREEN, BLUE, unit_point);
			}
			put_pixel_img(scene->image, r_t.pixel_x, r_t.pixel_y, color);
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