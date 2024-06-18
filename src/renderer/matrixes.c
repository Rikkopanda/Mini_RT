/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:29:35 by rverhoev          #+#    #+#             */
/*   Updated: 2024/06/18 13:45:23 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_t_around_z(t_vec4f R[3], float rad)
{
	R[0][0] = cos(rad);
	R[0][1] = sin(-rad);
	R[0][2] = 0;
	R[0][3] = 0;
	R[1][0] = sin(rad);
	R[1][1] = cos(rad);
	R[1][2] = 0;
	R[1][3] = 0;
	R[2][0] = 0;
	R[2][1] = 0;
	R[2][2] = 1;
	R[2][3] = 0;
}

void	init_t_around_y(t_vec4f R[3], float rad)
{
	R[0][0] = cos(rad);
	R[0][1] = 0;
	R[0][2] = sin(rad);
	R[0][3] = 0;
	R[1][0] = 0;
	R[1][1] = 1;
	R[1][2] = 0;
	R[1][3] = 0;
	R[2][0] = -sin(rad);
	R[2][1] = 0;
	R[2][2] = cos(rad);
	R[2][3] = 0;
}

void	init_t_around_x(t_vec4f R[3], float rad)
{
	R[0][0] = 1;
	R[0][1] = 0;
	R[0][2] = 0;
	R[0][3] = 0;

	R[1][0] = 0;
	R[1][1] = cos(rad);
	R[1][2] = -sin(rad);
	R[1][3] = 0;

	R[2][0] = 0;
	R[2][1] = sin(rad);
	R[2][2] = cos(rad);
	R[2][3] = 0;

}

void	init_result(t_vec4f *M)
{
	// int	i;

	// i = 0;
	// M = (t_vec4f)0;
	*M = (t_vec4f){0,0,0,0};
	// ft_bzero(M, 16);
	// print_matrix_1_3(*M);
	// while (i < 4)
	// {
	// 	(*M)[i] = 0;
	// 	i++;
	// }
}

void	init_identy_matrix(t_vec4f m[3])
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
}