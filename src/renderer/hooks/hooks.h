/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:56:52 by rverhoev          #+#    #+#             */
/*   Updated: 2024/08/09 15:07:17 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "minirt.h"

int			select_obj_to_move(int keysym, t_scene_data *data);
int			extra_keys(int keysym, t_scene_data *data);
int			left_up_right_down_forward_backward(int keysym, \
				t_scene_data *data);
t_object	*retrieve_move_obj(t_scene_data *data);
int			select_obj_to_move(int keysym, \
				t_scene_data *data);
int			move_object(int keysym, \
				t_scene_data *data, t_object *object_to_move);
void		rotate(t_scene_data *data, \
				int incr_sign, int index, char *print_literal);
int			rotate_view(int keysym, t_scene_data *data);

#endif