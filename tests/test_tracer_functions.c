/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tracer_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:01:10 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 16:32:39 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * just a test
 */
void 	test_reflect_function()
{
	t_vec4f	incoming;
	t_vec4f	surface_hit_pos;
	t_vec4f	surface_normal;
	t_vec4f	reflection;
	t_vec4f	diffuse_ray;
	t_vec4f	new_direction;

	incoming = (t_vec4f){0, 0, -1, 1};
	surface_hit_pos = (t_vec4f){20, 40, 60, 1};
	surface_normal = (t_vec4f){0, 0, 1, 1};
	reflection = reflect(surface_normal, incoming);
	printf("reflection\n");
	print_matrix_1_3(reflection);
	diffuse_ray = generate_random_vec4f_hemisphere(surface_normal);
	printf("surface normal\n");
	print_matrix_1_3(surface_normal);
	normalize_vector(&diffuse_ray);
	printf("diffuse_ray\n");
	print_matrix_1_3(diffuse_ray);
	new_direction = lerp(diffuse_ray, reflection, 1);
	printf("result\n");
	normalize_vector(&new_direction);
	print_matrix_1_3(new_direction);
	exit(0);
}
