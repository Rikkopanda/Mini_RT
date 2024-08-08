/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_color_functions_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:04:39 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/08 14:24:33 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

void make_rgb_with_normalized_rgb_f(int rgb[3], t_vec4f rgb_f)
{
	rgb[0] = (rgb_f[0] * (float)255);
	rgb[1] = (rgb_f[1] * (float)255);
	rgb[2] = (rgb_f[2] * (float)255);
}

int create_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	color_strength(int color, float strength)
{
	t_vec4f	rgb;

	rgb = int_to_vec4rgb(color);
	rgb *= strength;
	rgb[0] = ft_min(rgb[0], 255);
	rgb[1] = ft_min(rgb[1], 255);
	rgb[2] = ft_min(rgb[2], 255);
	return (vec4rgb_to_int(rgb));
}