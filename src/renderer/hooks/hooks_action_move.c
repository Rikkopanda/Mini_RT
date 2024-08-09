/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_action_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:26:30 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 13:46:34 by rverhoev         ###   ########.fr       */
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


t_object *retrieve_object_to_move(t_scene_data *data)
{
	t_object *current = data->objects;
	int i = 0;

	while (current != NULL)
	{		
		if (i == data->move_obj_number)
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
		data->move_obj_number = keysym - 48;
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
