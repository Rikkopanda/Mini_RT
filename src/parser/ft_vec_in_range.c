/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vec_in_range.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:11:01 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:11:08 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_vec_in_range(t_vec4f vec4f, float low, float high)
{
	if (high < low)
		swapf(&high, &low);
	if (vec4f[0] < low || vec4f[0] > high)
		return (0);
	if (vec4f[1] < low || vec4f[1] > high)
		return (0);
	if (vec4f[2] < low || vec4f[2] > high)
		return (0);
	if (vec4f[3] < low || vec4f[3] > high)
		return (0);
	return (1);
}
