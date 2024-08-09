/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:17:07 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/09 12:19:38 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
