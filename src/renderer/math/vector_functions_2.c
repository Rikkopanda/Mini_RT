/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_functions_2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 12:19:24 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/08/12 19:04:47 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot3(t_vec4f vec_A, t_vec4f vec_B)
{
	return ((vec_A[0] * vec_B[0]) + \
		(vec_A[1] * vec_B[1]) + (vec_A[2] * vec_B[2]));
}

t_vec4f	cross3(t_vec4f vec_A, t_vec4f vec_B)
{
	return ((t_vec4f){
		(vec_A[1] * vec_B[2]) - (vec_B[1] * vec_A[2]), \
		(vec_A[2] * vec_B[0]) - (vec_B[2] * vec_A[0]), \
		(vec_A[0] * vec_B[1]) - (vec_B[0] * vec_A[1]), vec_A[3]});
}

float	vector_length(t_vec4f v)
{
	return (sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

void	vector_scaling(t_vec4f *v, float scale)
{
	*v = *v * scale;
}
