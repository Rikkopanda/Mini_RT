/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_action_rotate.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:26:30 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/08/15 14:40:43 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minirt.h"

void	rotate(t_scene_data *data, const t_vec4f axis, \
				float radians, char *print_literal)
{
	t_vec4f	q_rotate;

	q_rotate = axis_angle_to_quaternion(axis, radians);
	print_matrix_1_3(q_rotate);
	data->camera.orientation = \
					hamilton_product(data->camera.orientation, q_rotate);
	printf("%s", print_literal);
}

int	rotate_view(int keysym, t_scene_data *data)
{
	if (keysym == UP)
		return (rotate(data, (t_vec4f){1, 0, 0, 1}, \
				DEGR_10_IN_RAD, ("rotating up...\n")), TRUE);
	else if (keysym == DOWN)
		return (rotate(data, (t_vec4f){1, 0, 0, 1}, \
				-DEGR_10_IN_RAD, ("rotating down...\n")), TRUE);
	else if (keysym == RIGHT)
		return (rotate(data, (t_vec4f){0, 1, 0, 1}, \
				-DEGR_10_IN_RAD, ("rotating right...\n")), TRUE);
	else if (keysym == LEFT)
		return (rotate(data, (t_vec4f){0, 1, 0, 1}, \
				DEGR_10_IN_RAD, ("rotating left...\n")), TRUE);
	return (FALSE);
}
