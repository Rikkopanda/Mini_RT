/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:19:24 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 16:17:01 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f	clamp_vec4f(t_vec4f v, float low, float high)
{
	t_vec4f	result;

	result[0] = fminf(fmaxf(v[0], low), high);
	result[1] = fminf(fmaxf(v[1], low), high);
	result[2] = fminf(fmaxf(v[2], low), high);
	result[3] = fminf(fmaxf(v[3], low), high);
	return (result);
}
