/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:29:32 by rverhoev          #+#    #+#             */
/*   Updated: 2024/06/18 13:54:04 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_comp_m(t_vec4f comp[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 4)
		{
			comp[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	compilation_matrix(t_vec4f comp[3], t_vec4f R[3], t_vec4f R3[3])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	init_identy_matrix(comp);
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				comp[i][j] += R[i][k] * R3[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

// void	copy_matrix(t_vec4f *dst, t_vec4f src)
// {
// 	int i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		(*dst)[i] = src[i];
// 		i++;
// 	}
// }
void	construct_4x4vec4f(t_vec4f translate, t_vec4f rotation[3], t_vec4f *transform_result[4])
{
	(*transform_result)[0] = (t_vec4f){0,0,0,0};

	(*transform_result)[0] = rotation[0];
	(*transform_result)[1] = rotation[1];
	(*transform_result)[2] = rotation[2];
	(*transform_result)[3] = translate;
}


void	matrix_multiply_1x3_3x3(t_vec4f *m1, t_vec4f m2[3], t_vec4f *result_m)
{
	int	i;
	int	j;

	init_result(result_m);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			(*result_m)[i]
				+= (*m1)[j]
				* m2[j][i];
			j++;
		}
		i++;
	}
}
void	matrix_multiply_3x3_3x3(t_vec4f a[3], t_vec4f b[3], t_vec4f result_m[3])
{
	int i;
	int j;
	int k;
 for(i=0;i< 3;i++)
 {
  for(j=0;j< 3;j++)
  {
   result_m[i][j] = 0;
   for(k=0;k< 3;k++)
   {
    result_m[i][j] = result_m[i][j] + a[i][k]*b[k][j];
   }
  }
 }
}

float	get_magnitude(t_vec4f v)
{
	float magnitude;

	magnitude = sqrt(powf(v[0], 2) + powf(v[1], 2) + powf(v[2], 2));
	return (magnitude);
}

void	vector_scaling(t_vec4f *v, float scale)
{
	*v = *v * scale;
}

float	ft_rad_to_degr(float x)
{
	if (x == 0)
		return (0);
	x = (x / (2 * M_PI)) * (float)360;
	return (x);
}

float	ft_degr_to_rad(float x)
{
	if (x == 0)
		return (0);
	x = (x * M_PI) / (float)180;
	return (x);
}

void	print_matrix_1_3(t_vec4f m)
{
	int i;

	i = 0;
	while (i < 3)
	{
		printf("%f\t", m[i]);
		i++;
	}
	printf("\n");
	// printf("_________________\n");
}

void	print_matrix_3_3(t_vec4f m[3])
{
	int i;
	int j;

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