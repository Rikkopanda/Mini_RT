/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clamped_rgb_to_int.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:22:15 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:22:16 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	clamped_rgb_to_int(int r, int g, int b)
{
	r = ft_max(ft_min(r, 255), 0);
	g = ft_max(ft_min(g, 255), 0);
	b = ft_max(ft_min(b, 255), 0);
	return ((r << 16) | (g << 8) | b);
}
