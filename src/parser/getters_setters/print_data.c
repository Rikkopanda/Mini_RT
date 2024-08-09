/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 15:20:14 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:08:52 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere_data(void *object)
{
	const t_sphere	*sphere = (t_sphere *)object;

	printf("data sphere: x, y, z %f %f %f\n", sphere->location[0], \
								sphere->location[1], sphere->location[2]);
}

void	print_cylinder_data(void *object)
{
	const t_cylinder	*cylinder = (t_cylinder *)object;

	printf("data cylinder: x, y, z %f %f %f\n", cylinder->location[0], \
								cylinder->location[1], cylinder->location[2]);
}

void	print_camera_data(void *object)
{
	const t_camera	*camera = (t_camera *)object;

	printf("data camera: x, y, z %f %f %f\n", camera->location[0], \
								camera->location[1], camera->location[2]);
}

void	print_plane_data(void *object)
{
	const t_plane	*plane = (t_plane *)object;

	printf("data plane: x, y, z %f %f %f\n", plane->location[0], \
								plane->location[1], plane->location[2]);
}

void	print_light_data(void *object)
{
	const t_light	*light = (t_light *)object;

	printf("data light: x, y, z %f %f %f\n", light->location[0], \
								light->location[1], light->location[2]);
}
