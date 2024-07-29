/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:26:30 by rverhoev          #+#    #+#             */
/*   Updated: 2024/07/29 18:46:21 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minirt.h"

int select_obj_to_move(int keysym, t_scene_data *data);

int	extra_keys(int keysym, t_scene_data *data)
{
	if (select_obj_to_move(keysym, data) == TRUE)
		return (TRUE);
	else if (keysym == ON_ESC)
		return (mlx_loop_end(data->mlx.mlx_ptr), -1);
	else
		return (FALSE);
}

int	left_up_right_down_forward_backward(int keysym, t_scene_data *data)
{
	const int dist = 10;
	if (keysym == 'd')
		return (printf("move camara x+...\n"), data->camera.location[0] += dist, 1);
	else if (keysym == 'a')
		return (printf("move camara x-...\n"), data->camera.location[0] -= dist, 1);	
	else if (keysym == 'r')
		return (printf("move camara y+...\n"), data->camera.location[1] += dist, 1);	
	else if (keysym == 'f')
		return (printf("move camara y-...\n"), data->camera.location[1] -= dist, 1);	
	else if (keysym == 's')
		return (printf("move camara z+...\n"), data->camera.location[2] += dist, 1);	
	else if (keysym == 'w')
		return (printf("move camara z-...\n"), data->camera.location[2] -= dist, 1);
	else
		return (0);
}

int move_obj_number = 0;

t_object *retrieve_object_to_move(t_scene_data *data)
{
	t_object *current = data->objects;
	int i = 0;

	while (current != NULL)
	{		
		if (i == move_obj_number)
			return current;
		current = current->next;
		i++;
	}
	return (t_object *)NADA;
}

int select_obj_to_move(int keysym, t_scene_data *data)
{
	if (ft_isdigit(keysym) == TRUE)
	{
		move_obj_number = keysym - 48;
		return TRUE;
	}
	return FALSE;
}

/**
 * initial value for index of object to move in the objectlist = 0
 */
int move_object(int keysym, t_scene_data *data)
{
	const int dist = 10;

	t_object *object_to_move = retrieve_object_to_move(data);
	if (object_to_move == (t_object *)NADA)
		return 1;
	if (keysym == 'l')
		return (printf("move lighting x+...\n"), object_to_move->set_location(object_to_move->object, 0, dist), 1);
	else if (keysym == 'j')
		return (printf("move lighting x-...\n"), object_to_move->set_location(object_to_move->object, 0, -dist), 1);	
	else if (keysym == 'p')
		return (printf("move lighting y+...\n"), object_to_move->set_location(object_to_move->object, 1, dist), 1);	
	else if (keysym == 'o')
		return (printf("move lighting y-...\n"), object_to_move->set_location(object_to_move->object, 1, -dist), 1);	
	else if (keysym == 'k')
		return (printf("move lighting z+...\n"), object_to_move->set_location(object_to_move->object, 2, dist), 1);	
	else if (keysym == 'i')
		return (printf("move lighting z-...\n"), object_to_move->set_location(object_to_move->object, 2, -dist), 1);
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
	const int	degrees = 10;
	const int	rotation_max = 180;
	if (keysym == UP)
	{
		data->camera.orientation[0] += degrees;
		if (data->camera.orientation[0] > rotation_max)
			data->camera.orientation[0] = -rotation_max + degrees;
		return (printf("rotating up...\n"), TRUE);
	}
	else if (keysym == DOWN)
	{
		data->camera.orientation[0] -= degrees;
		if (data->camera.orientation[0] < -rotation_max)
			data->camera.orientation[0] = rotation_max - degrees;
		return (printf("rotating down...\n"), TRUE);
	}
	else if (keysym == RIGHT)
	{
		data->camera.orientation[1] -= degrees;
		if (data->camera.orientation[1] < -rotation_max)
			data->camera.orientation[1] = rotation_max - degrees;
		return (printf("rotating right...\n"), TRUE);

	}
	else if (keysym == LEFT)
	{
		data->camera.orientation[1] += degrees;
		if (data->camera.orientation[1] > rotation_max)
			data->camera.orientation[1] = -rotation_max + degrees;
		return (printf("rotating left...\n"), TRUE);
	}
	return (FALSE);
}

/**
 * @note putting all into a while() to select function pointer could be faster than if else's?
 * 
*/
int handle_input(int keysym, t_scene_data *data)
{
	printf("keysym %d\n", keysym);
	if (left_up_right_down_forward_backward(keysym, data) == FALSE
		&& rotate_view(keysym, data) == FALSE
		&& extra_keys(keysym, data) == FALSE
		&& move_object(keysym, data) == FALSE)
		return (0);
	if (extra_keys(keysym, data))
		return (0);
	send_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->image.img_ptr, 0, 0);
	// printf("%d key\n", keysym);
    return (0);
}
