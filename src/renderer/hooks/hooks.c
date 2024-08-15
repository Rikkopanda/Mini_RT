/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:26:30 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/08/15 17:17:45 by rverhoev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minirt.h"
#include "hooks.h"

int	handle_input(int keysym, t_scene_data *data)
{
	if (left_up_right_down_forward_backward(keysym, data) == FALSE
		&& rotate_view(keysym, data) == FALSE
		&& extra_keys(keysym, data) == FALSE
		&& move_object(keysym, retrieve_move_obj(data)) == FALSE)
		return (0);
	if (extra_keys(keysym, data))
		return (0);
	send_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, \
		data->mlx.win_ptr, data->image.img_ptr, 0, 0);
	print_matrix_1_3(data->camera.orientation);
	print_matrix_1_3(data->camera.location);
	return (0);
}
