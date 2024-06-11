/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:29:35 by rverhoev          #+#    #+#             */
/*   Updated: 2024/06/11 13:06:33 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_t_around_z(t_vec4f R[3], float rad)
{
	R[0][0] = cos(rad);
	R[0][1] = sin(-rad);
	R[0][2] = 0;
	R[1][0] = sin(rad);
	R[1][1] = cos(rad);
	R[1][2] = 0;
	R[2][0] = 0;
	R[2][1] = 0;
	R[2][2] = 1;
}

void	init_t_around_y(t_vec4f R[3], float rad)
{
	R[0][0] = cos(rad);
	R[0][1] = 0;
	R[0][2] = sin(rad);
	R[1][0] = 0;
	R[1][1] = 1;
	R[1][2] = 0;
	R[2][0] = -sin(rad);
	R[2][1] = 0;
	R[2][2] = cos(rad);
}

void	init_t_around_x(t_vec4f R[3], float rad)
{
	R[0][0] = 1;
	R[0][1] = 0;
	R[0][2] = 0;
	R[1][0] = 0;
	R[1][1] = cos(rad);
	R[1][2] = -sin(rad);
	R[2][0] = 0;
	R[2][1] = sin(rad);
	R[2][2] = cos(rad);
}

void	init_result(t_vec4f M)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		M[i] = 0;
		i++;
	}
}
