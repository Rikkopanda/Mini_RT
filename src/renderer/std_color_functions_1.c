/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_color_functions_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:04:39 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/08 14:22:49 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_r(int color)
{
	return (color >> 16 & 0xFF);
}

int	get_g(int color)
{
	return (color >> 8 & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}

void init_rgb(t_color *color, int color_code)
{
	color->rgb[0] = get_r(color_code);
	color->rgb[1] = get_g(color_code);
	color->rgb[2] = get_b(color_code);
}

void init_rgb_f(t_vec4f *rgb_f, int rgb[3])
{
	(*rgb_f)[0] = rgb[0];
	(*rgb_f)[1] = rgb[1];
	(*rgb_f)[2] = rgb[2];
	(*rgb_f)[3] = 0;
}
