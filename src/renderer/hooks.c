/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:26:30 by rverhoev          #+#    #+#             */
/*   Updated: 2024/06/12 14:22:22 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minirt.h"

int	extra_keys(int keysym, t_scene_data *data)
{
	if (keysym == ON_ESC)
		return (mlx_loop_end(data->mlx.mlx_ptr), -1);
	else
		return (FALSE);
}

int	left_up_right_down_forward_backward(int keysym, t_scene_data *data)
{
	if (keysym == 'w')
		return (data->camera.location[0] += 10, 1);
	else if (keysym == 's')
		return (data->camera.location[0] -= 10, 1);	
	else if (keysym == 'a')
		return (data->camera.location[1] += 10, 1);	
	else if (keysym == 'd')
		return (data->camera.location[1] -= 10, 1);	
	else if (keysym == 'r')
		return (data->camera.location[2] += 10, 1);	
	else if (keysym == 'f')
		return (data->camera.location[2] -= 10, 1);
	else
		return (0);
}

int move_lighting(int keysym, t_scene_data *data)
{
	if (keysym == 'i')
		return (data->light.location[0] += 50, 1);
	else if (keysym == 'k')
		return (data->light.location[0] -= 50, 1);	
	else if (keysym == 'j')
		return (data->light.location[1] += 50, 1);	
	else if (keysym == 'l')
		return (data->light.location[1] -= 50, 1);	
	else if (keysym == 'o')
		return (data->light.location[2] += 50, 1);	
	else if (keysym == 'p')
		return (data->light.location[2] -= 50, 1);
	else
		return (0);
}

// int	rotate_around_z(int keysym, t_scene_data *data)
// {
// }
// int	rotate_around_y(int keysym, t_scene_data *data)
// {
// }

int	rotate_view(int keysym, t_scene_data *data)
{
	t_vec4f	add_angle[3];
	t_vec4f	original_orientation_matrix;

	init_comp_m(add_angle);
	copy_matrix(&original_orientation_matrix, data->camera.orientation);
	if (keysym == UP)
	{
		init_t_around_y(add_angle, DEGR_10_IN_RAD);
		matrix_multiply_1x3_3x3(&original_orientation_matrix, add_angle, &data->camera.orientation);	
		return (printf("rotating...\n"), TRUE);
	}
	else if (keysym == DOWN)
	{
		init_t_around_y(add_angle, -DEGR_10_IN_RAD);
		matrix_multiply_1x3_3x3(&original_orientation_matrix, add_angle, &data->camera.orientation);
		return (printf("rotating...\n"), TRUE);
	}
	else if (keysym == LEFT)
	{
		init_t_around_z(add_angle, DEGR_10_IN_RAD);
		matrix_multiply_1x3_3x3(&original_orientation_matrix, add_angle, &data->camera.orientation);
		return (printf("rotating...\n"), TRUE);

	}
	else if (keysym == RIGHT)
	{
		init_t_around_z(add_angle, -DEGR_10_IN_RAD);
		matrix_multiply_1x3_3x3(&original_orientation_matrix, add_angle, &data->camera.orientation);
		return (printf("rotating...\n"), TRUE);
	}
	return (FALSE);
}

/**
 * @note putting all into a while() to select function pointer could be faster than if else's?
 * 
*/
int handle_input(int keysym, t_scene_data *data)
{
	if (left_up_right_down_forward_backward(keysym, data) == FALSE
		&& rotate_view(keysym, data) == FALSE
		&& extra_keys(keysym, data) == FALSE
		&& move_lighting(keysym, data) == FALSE)
		return (0);
	send_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->image.img_ptr, 0, 0);
	printf("%d key\n", keysym);
    return (0);
}
