/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_vec_gen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:59:57 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/08 14:23:19 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @note Variation of Knuth's multiplicative method.
 */
float	knuth_hash(unsigned int *seed)
{
	*seed = ((*seed + 1) * 26761) % (1 << 27);
	return ((float)*seed / __INT_MAX__);
}
/**
 * @note Box-Muller transform to turn uniformly distributed random numbers 
 * to normal distributed
 * From: 
 */
float	random_normal_distribution(unsigned int *seed)
{
	const float	theta = 2 * M_PI * knuth_hash(seed);
	const float	rho = sqrtf(-2 * log(knuth_hash(seed)));

	return (rho * cos(theta));
}
/**
 * @note Unused at the moment, will be used for global illumination.
 */
t_vec4f	generate_random_vec4f(void)
{
	static unsigned int	seed = 0;
	t_vec4f				vec4f;

	vec4f = (t_vec4f){
		random_normal_distribution(&seed),
		random_normal_distribution(&seed),
		random_normal_distribution(&seed),
		1,
	};
	normalize_vector(&vec4f);
	return (vec4f);
}
