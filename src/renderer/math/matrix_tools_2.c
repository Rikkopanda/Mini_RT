/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_tools_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/07 15:29:32 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/08/14 16:08:08 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
