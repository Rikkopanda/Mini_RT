/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:09:28 by rverhoev          #+#    #+#             */
/*   Updated: 2024/07/26 17:09:38 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f t_get_location_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return sphere->location;
}

t_vec4f	t_get_color_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return (sphere->color.rgb_f);
}

float	t_get_smoothness_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return (sphere->smoothness);
}