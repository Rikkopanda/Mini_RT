/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 17:09:23 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:09:24 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>

# include "minirt.h"

/* parser lib functions */
void		swapf(float *a, float *b);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
float		ft_atof(const char *s);
int			ft_rgb_to_int(const char *a_rgb);
t_vec4f		atovec3f(const char *a_vec3f);
int			ft_vec_in_range(t_vec4f vec4f, float low, float high);
int			clamped_rgb_to_int(int r, int g, int b);
char		**ft_split_charset(const char *s, const char *set);
char		*ft_str_endswith(const char *s, const char *end);
size_t		ft_2darray_size(char **arr);
void		ft_free_2darray(char **array);

int			parse_ambient(t_object **objects, char **format);
int			parse_camera(t_object **objects, char **format);
int			parse_light(t_object **objects, char **format);
int			parse_sphere(t_object **objects, char **format);
int			parse_plane(t_object **objects, char **format);
int			parse_cylinder(t_object **objects, char **format);
int			parse_object(const char *line, int obj_count[OBJ_TYPE_COUNT], \
						t_object **objects);
int			parse_rt_file(t_scene_data *scene, int fd);

#endif