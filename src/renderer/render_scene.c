/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:53:18 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/09 17:44:53 by rverhoev         ###   ########.fr       */
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
	mlx_loop(data->mlx.mlx_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	destroy_image(data->image);
	free(data->mlx.mlx_ptr);
	return (0);
}
