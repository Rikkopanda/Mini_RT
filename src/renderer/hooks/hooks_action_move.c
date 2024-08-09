/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_action_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:26:30 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 17:59:00 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minirt.h"

int	select_obj_to_move(int keysym, t_scene_data *data);

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
	const int	dist = 10;

	if (keysym == 'd')
		return (printf("move camara x+...\n"),
			data->camera.location[0] += dist, 1);
	else if (keysym == 'a')
		return (printf("move camara x-...\n"),
			data->camera.location[0] -= dist, 1);
	else if (keysym == 'r')
		return (printf("move camara y+...\n"),
			data->camera.location[1] += dist, 1);
	else if (keysym == 'f')
		return (printf("move camara y-...\n"),
			data->camera.location[1] -= dist, 1);
	else if (keysym == 's')
		return (printf("move camara z+...\n"),
			data->camera.location[2] += dist, 1);
	else if (keysym == 'w')
		return (printf("move camara z-...\n"),
			data->camera.location[2] -= dist, 1);
	else
		return (0);
}

t_object	*retrieve_move_obj(t_scene_data *data)
{
	t_object	*current;
	int			i;

	i = 0;
	current = data->objects;
	while (current != NULL)
	{
		if (i == data->move_obj_number)
			return (current);
		current = current->next;
		i++;
	}
	return ((t_object *)NADA);
}

int	select_obj_to_move(int keysym, t_scene_data *data)
{
	if (ft_isdigit(keysym) == TRUE)
	{
		data->move_obj_number = keysym - 48;
		return (TRUE);
	}
	return (FALSE);
}

/**
 * initial value for index of object to move in the objectlist = 0
 */
int	move_object(int keysym, t_object *move_obj)
{
	if (move_obj == (t_object *)NADA)
		return (TRUE);
	if (keysym == 'l')
		return (move_obj->set_location(move_obj->object, 0, MOVE_DIST),
			printf("move lighting x+...\n"), TRUE);
	else if (keysym == 'j')
		return (printf("move lighting x-...\n"),
			move_obj->set_location(move_obj->object, 0, -MOVE_DIST), TRUE);
	else if (keysym == 'p')
		return (printf("move lighting y+...\n"),
			move_obj->set_location(move_obj->object, 1, MOVE_DIST), TRUE);
	else if (keysym == 'o')
		return (printf("move lighting y-...\n"),
			move_obj->set_location(move_obj->object, 1, -MOVE_DIST), TRUE);
	else if (keysym == 'k')
		return (printf("move lighting z+...\n"),
			move_obj->set_location(move_obj->object, 2, MOVE_DIST), TRUE);
	else if (keysym == 'i')
		return (printf("move lighting z-...\n"),
			move_obj->set_location(move_obj->object, 2, -MOVE_DIST), TRUE);
	else
		return (FALSE);
}
