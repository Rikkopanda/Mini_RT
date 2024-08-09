/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambient.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 16:51:57 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:05:50 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int	parse_ambient(t_object **objects, char **format)
{
	t_ambient	*ambient;
	t_object	*new;

	if (ft_2darray_size(format) != 2)
	{
		fprintf(stderr, "Error: incorrect ambient lighting info format.\n");
		return (0);
	}
	ambient = malloc(sizeof(*ambient));
	if (!ambient)
		return (perror("malloc error"), 0);
	ambient->ratio = ft_atof(format[0]);
	if (ambient->ratio < 0.0f || ambient->ratio > 1.0f)
	{
		fprintf(stderr, "Error: %.2f: ambient lighting ratio \
out of range [0.0, 1.0]\n", ambient->ratio);
		return (free(ambient), 0);
	}
	ambient->color.color_code = ft_rgb_to_int(format[1]);
	ambient->color.rgb_f = int_to_vec4rgb(ambient->color.color_code);
	new = new_object(AMBIENT, ambient);
	if (!new)
		return (perror("malloc error"), free(ambient), 0);
	append_object(objects, new);
	return (1);
}
