/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:10:04 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:10:21 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));

typedef struct s_color
{
	int		rgb[3];
	int		color_code;
	t_vec4f	rgb_f;
}	t_color;

int	get_r(int color);
int	get_g(int color);
int	get_b(int color);

#endif