#include "minirt.h"

void init_ray_send_tools(t_ray_sending_tools *r_t, t_scene_data *scene)
{
	r_t->half_screen_width = WINDOW_WIDTH * 0.5;
	r_t->half_screen_height = WINDOW_HEIGHT * 0.5;
	r_t->start_angle_horiz = ft_degr_to_rad((float)scene->camera.fov)  * 0.5;
	r_t->start_angle_vert = ft_degr_to_rad((float)scene->camera.fov) * 0.5;
	printf("%f\t%f\n", r_t->start_angle_horiz, r_t->start_angle_vert);
	r_t->perpendicular_distance_horiz_triangle = r_t->half_screen_width / (float)tan(r_t->start_angle_horiz);
	r_t->perpendicular_distance_vert_triangle = r_t->half_screen_height / (float)tan(r_t->start_angle_vert);
	printf("%f\t%f\n", r_t->perpendicular_distance_vert_triangle, r_t->perpendicular_distance_horiz_triangle);
	// exit(0);

}

void	init_light_source(t_scene_data *data)
{
	data->light.brightness = 1;
	data->light.location[0] = 0;
	data->light.location[1] = 0;
	data->light.location[2] = -100;
	data->light.location[3] = 0;
	data->light.color.rgb[0] = 255;
	data->light.color.rgb[1] = 255;
	data->light.color.rgb[2] = 255;
}

// void	init_sphere(t_scene_data *data)
// {
// 	data->sphere.radius = 30;
// 	data->sphere.color.color_code = ORANGE;
// 	data->sphere.location[0] = 100;
// 	data->sphere.location[1] = 40;
// 	data->sphere.location[2] = 0;
// 	data->sphere.location[3] = 0;
// }

void	init_camera(t_scene_data *data)
{
	data->camera.fov = 70;
	data->camera.orientation[0] = 1;
	data->camera.orientation[1] = 0;
	data->camera.orientation[2] = 0;
	data->camera.orientation[3] = 0;
	data->camera.location[0] = 0;
	data->camera.location[1] = 0;
	data->camera.location[2] = 0;
	data->camera.location[3] = 0;
	// if (PRINT_DEBUG) printf("original\n");
	// if (PRINT_DEBUG) print_matrix_1_3(data->camera.orientation);
}

int render_scene(t_scene_data *data)
{

	data->mlx = new_window(data->win_width, data->win_height, "My first window");
	if (!data->mlx.win_ptr)
		return (1);
	data->image = new_img(data->win_width, data->win_height, data->mlx);

	mlx_key_hook(data->mlx.win_ptr, handle_input, data);

	// init_camera(data);
	init_light_source(data);
	// init_sphere(data);
	// printf("data object: x, y, z %d %d %d\n", );
	send_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->image.img_ptr, 0, 0);
	mlx_loop(data->mlx.mlx_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	destroy_image(data->image);
	free(data->mlx.mlx_ptr);
	return (0);
}
