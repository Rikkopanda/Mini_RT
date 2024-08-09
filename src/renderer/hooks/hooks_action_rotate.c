/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_action_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:26:30 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 14:44:54 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minirt.h"

#define DEGREES 10
#define ROTATION_MAX 180

void	rotate(t_scene_data *data, int incr_sign, \
	int index, char *print_literal)
{
	if (incr_sign == 1)
	{
		if (data->camera.orientation[index] > ROTATION_MAX)
			data->camera.orientation[index] \
				= -ROTATION_MAX + (DEGREES * incr_sign);
		else
			data->camera.orientation[index] += (DEGREES * incr_sign);
	}
	else
	{
		if (data->camera.orientation[index] < -ROTATION_MAX)
			data->camera.orientation[index] \
				= -ROTATION_MAX + (DEGREES * incr_sign);
		else
			data->camera.orientation[index] += (DEGREES * incr_sign);
	}
	printf("%s", print_literal);
}

int	rotate_view(int keysym, t_scene_data *data)
{
	const int	rotation_max = 180;

	if (keysym == UP)
		return (rotate(data, 1, 0, ("rotating up...\n")), TRUE);
	else if (keysym == DOWN)
		return (rotate(data, -1, 0, ("rotating down...\n")), TRUE);
	else if (keysym == RIGHT)
		return (rotate(data, 1, 1, ("rotating right...\n")), TRUE);
	else if (keysym == LEFT)
		return (rotate(data, -1, 1, ("rotating left...\n")), TRUE);
	return (FALSE);
}
