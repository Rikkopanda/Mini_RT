#include "parser.h"
#include "libft.h"
#include "minirt.h"

void init_ray_send_tools(t_ray_sending_tools *r_t, t_scene_data *scene)
{
	r_t->half_screen_width = WINDOW_WIDTH * 0.5;
	r_t->half_screen_height = WINDOW_HEIGHT * 0.5;
	r_t->start_angle_horiz = ft_degr_to_rad((float)scene->camera.fov)  * 0.5;
	r_t->start_angle_vert = ft_degr_to_rad((float)scene->camera.fov) * 0.5;
	r_t->perpendicular_distance_horiz_triangle = r_t->half_screen_width / (float)tan(r_t->start_angle_horiz);
	r_t->perpendicular_distance_vert_triangle = r_t->half_screen_height / (float)tan(r_t->start_angle_vert);
}

void render_scene(t_scene_data *data)
{
	send_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->image.img_ptr, 0, 0);
	mlx_loop(data->mlx.mlx_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	destroy_image(data->image);
	free(data->mlx.mlx_ptr);
}
