/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:09:28 by rverhoev          #+#    #+#             */
/*   Updated: 2024/07/29 18:41:52 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f get_location_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return sphere->location;
}

void	set_location_sphere(void *object, int xyz_index, int addition)
{
	t_sphere *sphere = (t_sphere *)object;
	sphere->location[xyz_index] += addition;
}

t_vec4f	get_color_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return (sphere->color.rgb_f);
}

float	get_smoothness_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return (sphere->smoothness);
}
