/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_geometric_get_set.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:23:01 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:29:18 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_intersect(t_object *object)
{
	const t_intersect	intersect[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		intersect_light,
		intersect_sphere,
		intersect_plane,
		intersect_cylinder,
	};

	object->intersect = intersect[object->type];
}

void	assign_location_getter(t_object *object)
{
	const t_get_location	get_location[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		get_location_light,
		get_location_sphere,
		get_location_plane,
		get_location_cylinder,
	};

	object->get_location = get_location[object->type];
}

void	assign_location_setter(t_object *object)
{
	const t_set_location	set_location[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		set_location_light,
		set_location_sphere,
		set_location_plane,
		set_location_cylinder,
	};

	object->set_location = set_location[object->type];
}

void	assign_normal_getter(t_object *object)
{
	const t_get_normal		get_normal[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		get_normal_sphere,
		get_normal_plane,
		get_normal_cylinder,
	};

	object->get_normal = get_normal[object->type];
}
