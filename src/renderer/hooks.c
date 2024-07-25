/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:26:30 by rverhoev          #+#    #+#             */
/*   Updated: 2024/07/25 12:10:29 by rverhoev         ###   ########.fr       */
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
		return (printf("move camara x+...\n"), data->camera.location[0] += 10, 1);
	else if (keysym == 's')
		return (printf("move camara x-...\n"), data->camera.location[0] -= 10, 1);	
	else if (keysym == 'a')
		return (printf("move camara y+...\n"), data->camera.location[1] += 10, 1);	
	else if (keysym == 'd')
		return (printf("move camara y-...\n"), data->camera.location[1] -= 10, 1);	
	else if (keysym == 'r')
		return (printf("move camara z+...\n"), data->camera.location[2] += 10, 1);	
	else if (keysym == 'f')
		return (printf("move camara z-...\n"), data->camera.location[2] -= 10, 1);
	else
		return (0);
}

int move_lighting(int keysym, t_scene_data *data)
{
	if (keysym == 'i')
		return (printf("move lighting x+...\n"), data->light.location[0] += 50, 1);
	else if (keysym == 'k')
		return (printf("move lighting x-...\n"), data->light.location[0] -= 50, 1);	
	else if (keysym == 'j')
		return (printf("move lighting y+...\n"), data->light.location[1] += 50, 1);	
	else if (keysym == 'l')
		return (printf("move lighting y-...\n"), data->light.location[1] -= 50, 1);	
	else if (keysym == 'o')
		return (printf("move lighting z+...\n"), data->light.location[2] += 50, 1);	
	else if (keysym == 'p')
		return (printf("move lighting z-...\n"), data->light.location[2] -= 50, 1);
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
	int rotate_bool = 0;
	init_comp_m(add_angle);
	original_orientation_matrix = data->camera.orientation;
	if (keysym == UP)
	{
		t_vec4f	rota1[3];

		init_t_around_y(rota1, DEGR_10_IN_RAD);
		t_vec4f	placeholder[3];
		placeholder[0] = data->camera.rotation_comp[0];
		placeholder[1] = data->camera.rotation_comp[1];
		placeholder[2] = data->camera.rotation_comp[2];

		matrix_multiply_3x3_3x3(placeholder, rota1, data->camera.rotation_comp);
		return (printf("rotating up...\n"), TRUE);
	}
	else if (keysym == DOWN)
	{
		t_vec4f	rota2[3];
		t_vec4f	placeholder[3];

		init_t_around_y(rota2, -DEGR_10_IN_RAD);
		placeholder[0] = data->camera.rotation_comp[0];
		placeholder[1] = data->camera.rotation_comp[1];
		placeholder[2] = data->camera.rotation_comp[2];
		matrix_multiply_3x3_3x3(placeholder, rota2, data->camera.rotation_comp);
		return (printf("rotating down...\n"), TRUE);
	}
	else if (keysym == LEFT)
	{
		t_vec4f	rota3[3];
		t_vec4f	placeholder[3];

		init_t_around_z(rota3, DEGR_10_IN_RAD);
		placeholder[0] = data->camera.rotation_comp[0];
		placeholder[1] = data->camera.rotation_comp[1];
		placeholder[2] = data->camera.rotation_comp[2];
		// print_matrix_3_3(data->camera.rotation_comp);

		matrix_multiply_3x3_3x3(placeholder, rota3, data->camera.rotation_comp);

		// print_matrix_3_3(data->camera.rotation_comp);
		// print_matrix_3_3(data->camera.rotation_around_z);
		// matrix_multiply_1x3_3x3(&original_orientation_matrix, add_angle, &data->camera.orientation);
		return (printf("rotating left...\n"), TRUE);

	}
	else if (keysym == RIGHT)
	{
		t_vec4f	rota4[3];
		t_vec4f	placeholder[3];

		init_t_around_z(rota4, -DEGR_10_IN_RAD);
		placeholder[0] = data->camera.rotation_comp[0];
		placeholder[1] = data->camera.rotation_comp[1];
		placeholder[2] = data->camera.rotation_comp[2];
		matrix_multiply_3x3_3x3(placeholder, rota4, data->camera.rotation_comp);
		// matrix_multiply_1x3_3x3(&original_orientation_matrix, add_angle, &data->camera.orientation);
		return (printf("rotating right...\n"), TRUE);
	}
	// t_vec4f	rota_horiz[3];
	// t_vec4f	rota_vert[3];
	// t_vec4f	comp[3];

	// init_t_around_z(rota_horiz, pixel_angle_screen_space_x);
	// init_t_around_y(rota_vert, pixel_angle_screen_space_y);
	// init_comp_m(comp);
	// compilation_matrix(comp, rota_horiz, rota_vert);

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
	printf("sphere \n");

	print_matrix_1_3(data->objects->get_location(data->objects->object));
	printf("light \n");

	print_matrix_1_3(data->light.location);
	printf("%d key\n", keysym);
    return (0);
}
