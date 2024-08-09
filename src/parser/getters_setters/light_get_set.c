/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_get_set.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:21:12 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:13:48 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f	get_location_light(void *object)
{
	const t_light	*light = (t_light *)object;

	return (light->location);
}

void	set_location_light(void *object, int xyz_index, int addition)
{
	t_light	*light;

	light = (t_light *)object;
	light->location[xyz_index] += addition;
}

t_vec4f	get_color_light(void *object)
{
	const t_light	*light = (t_light *)object;

	return (light->color.rgb_f);
}

float	get_brightness_light(void *object)
{
	const t_light	*light = (t_light *)object;

	return (light->ratio);
}
