/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:41:06 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 15:21:12 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * https://www.freetext.org/Introduction_to_Linear_
 * Algebra/Basic_Vector_Operations/Normalization/
*/
void	normalize_vector(t_vec4f *v)
{
	float	magnitude;
	double	squared;

	squared = pow((double)(*v)[0], 2) + pow((double)(*v)[1], 2) \
		+ pow((double)(*v)[2], 2);
	magnitude = (float)sqrt(squared);
	*v = *v * (1.0f / magnitude);
}

void	print_vec4ftor(float vec[3])
{
	printf("x: %f, y: %f, z: %f\n", vec[0], vec[1], vec[2]);
}

t_vec4f	int_to_vec4rgb(int color)
{
	return ((t_vec4f){get_r(color), get_g(color), get_b(color), 1});
}

int	vec4rgb_to_int(t_vec4f vec)
{
	return ((int)vec[0] << 16 | (int)vec[1] << 8 | (int)vec[2]);
}
