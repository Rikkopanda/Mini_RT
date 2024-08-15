/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_scene.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 13:53:18 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/08/15 14:40:02 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render_scene(t_scene_data *data)
{
	data->mlx = new_window(data->win_width,
			data->win_height, "My first window");
	if (!data->mlx.win_ptr)
		return (1);
	data->image = new_img(data->win_width, data->win_height, data->mlx);
	mlx_key_hook(data->mlx.win_ptr, handle_input, data);
	send_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->image.img_ptr, 0, 0);
	print_matrix_1_3(data->camera.orientation);
	print_matrix_1_3(data->camera.location);
	mlx_loop(data->mlx.mlx_ptr);
	mlx_destroy_image(data->mlx.mlx_ptr, data->image.img_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	mlx_destroy_display(data->mlx.mlx_ptr);
	free(data->mlx.mlx_ptr);
	return (0);
}
