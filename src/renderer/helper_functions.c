/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:08:44 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/08 14:08:59 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	calculate_light_strength(float ratio, float distance, float strength)
{
	return (ratio / distance * strength);
}

float	ft_maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
