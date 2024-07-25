/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:26:30 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/07/25 15:18:11 by kwchu         ########   odam.nl         */
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

int move_lighting(int keysym, t_scene_data *data)
{
	const int dist = 10;
	if (keysym == 'l')
		return (printf("move lighting x+...\n"), data->light.location[0] += dist, 1);
	else if (keysym == 'j')
		return (printf("move lighting x-...\n"), data->light.location[0] -= dist, 1);	
	else if (keysym == 'p')
		return (printf("move lighting y+...\n"), data->light.location[1] += dist, 1);	
	else if (keysym == ';')
		return (printf("move lighting y-...\n"), data->light.location[1] -= dist, 1);	
	else if (keysym == 'k')
		return (printf("move lighting z+...\n"), data->light.location[2] += dist, 1);	
	else if (keysym == 'i')
		return (printf("move lighting z-...\n"), data->light.location[2] -= dist, 1);
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
	else if (keysym == LEFT)
	{
		data->camera.orientation[1] -= degrees;
		if (data->camera.orientation[1] < -rotation_max)
			data->camera.orientation[1] = rotation_max - degrees;
		return (printf("rotating left...\n"), TRUE);

	}
	else if (keysym == RIGHT)
	{
		data->camera.orientation[1] += degrees;
		if (data->camera.orientation[1] > rotation_max)
			data->camera.orientation[1] = -rotation_max + degrees;
		return (printf("rotating right...\n"), TRUE);
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
	if (extra_keys(keysym, data))
		return (0);
	send_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->image.img_ptr, 0, 0);
	// printf("%d key\n", keysym);
    return (0);
}
