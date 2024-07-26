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

t_vec4f t_get_location_light(void *object)
{
	t_light *light = (t_light *)object;

	return light->location;
}

t_vec4f	t_get_color_light(void *object)
{
	t_light *light = (t_light *)object;

	return (light->color.rgb_f);
}

float	t_get_brightness_light(void *object)
{
	t_light *light = (t_light *)object;

	return (light->ratio);
}
