/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_math.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 14:56:52 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/08/14 16:49:17 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MATH_H
# define MINI_MATH_H

# include "minirt.h"
# include "objects.h"

// matrix functions
void	matrix_multiplication(t_vec4f comp[3], \
			t_ray *ray, t_vec4f camera_vector);
void	matrix_multiply_1x3_3x3(t_vec4f *m1, t_vec4f m2[3], t_vec4f *result_m);
void	compilation_matrix(t_vec4f comp[3], t_vec4f R[3], t_vec4f R3[3]);
void	copy_matrix(t_vec4f *dst, t_vec4f src);
void	init_comp_m(t_vec4f comp[3]);

// vector functions
float	vector_length(t_vec4f v);
t_vec4f	clamp_vec4f(t_vec4f v, float low, float high);
float	dot3(t_vec4f vec_A, t_vec4f vec_B);
t_vec4f	cross3(t_vec4f vec_A, t_vec4f vec_B);
t_vec4f	lerp(t_vec4f a, t_vec4f b, float f);

// quaternion functions
t_vec4f	normalize_quaternion(t_vec4f *q);
t_vec4f	apply_rotation(t_vec4f point, t_vec4f rotation);
t_vec4f	invert_quaternion(t_vec4f quaternion);
t_vec4f	invert_unit_quaternion(t_vec4f uq);
t_vec4f	axis_angle_to_quaternion(t_vec4f axis, float angle_rad);
t_vec4f	hamilton_product(t_vec4f q1, t_vec4f q2);

#endif
