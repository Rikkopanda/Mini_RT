/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_tools_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 15:29:32 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/08/13 16:01:08 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int is_zero_vector3(t_vec4f a)
{
	return (a[0] == 0 && a[1] == 0 && a[2] == 0);
}

static t_vec4f	normalize_quaternion(t_vec4f *q)
{
	float	magnitude;
	float	squared;

	squared = powf((*q)[0], 2) + powf((*q)[1], 2) \
			+ powf((*q)[2], 2) + powf((*q)[3], 2);
	magnitude = sqrtf(squared);
	*q = *q / magnitude;
	return (*q);
}

t_vec4f	orientation_to_quaternion_rotation(t_vec4f orientation)
{
	t_vec4f			default_orientation = {0, 0, -1, 1};
	t_vec4f			cross_product;
	t_vec4f			quaternion;
	float			dot_product;
	const float		epsilon = -0.99999f;

	if (is_zero_vector3(orientation))
		return ((t_vec4f){0, 1, 0, 0});
	normalize_vector(&orientation);
	if (orientation[0] >= 0)
		cross_product = cross3(default_orientation, orientation);
	else
		cross_product = cross3(orientation, default_orientation);
	dot_product = dot3(default_orientation, orientation);
	// printf("orientation\n");
	// print_matrix_1_3(orientation);
	// printf("cross_product\n");
	// print_matrix_1_3(cross_product);
	// printf("dot %.4f\n", dot_product);
	if (dot_product < epsilon)
		return ((t_vec4f){1, cross_product[0], cross_product[1], cross_product[2]});
	quaternion[0] = 1 + dot_product;
	quaternion[1] = cross_product[0];
	quaternion[2] = cross_product[1];
	quaternion[3] = cross_product[2];
	return (normalize_quaternion(&quaternion));
}

void	print_matrix_1_3(t_vec4f m)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("%f\t", m[i]);
		i++;
	}
	printf("\n");
}

void	print_matrix_3_3(t_vec4f m[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			printf("%f\t", m[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}
