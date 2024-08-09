/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:09:28 by rverhoev          #+#    #+#             */
/*   Updated: 2024/07/26 17:09:38 by rverhoev         ###   ########.fr       */
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
	const t_light	*light = (t_light *)object;

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
