/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_material_get_set.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:24:08 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:31:27 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_color_getter(t_object *object)
{
	const t_get_color	get_color[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		get_color_light,
		get_color_sphere,
		get_color_plane,
		get_color_cylinder,
	};

	object->get_color = get_color[object->type];
}

void	assign_smoothness_getter(t_object *object)
{
	const t_get_smoothness	get_smoothness[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		get_smoothness_sphere,
		get_smoothness_plane,
		get_smoothness_cylinder,
	};

	object->get_smoothness = get_smoothness[object->type];
}

void	assign_brightness_getter(t_object *object)
{
	const t_get_brightness	get_brightness[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		get_brightness_light,
		NULL,
		NULL,
		NULL,
	};

	object->get_brightness = get_brightness[object->type];
}
