#ifndef DEBUG_INFO_H
# define DEBUG_INFO_H
# include "parser.h"

void	print_vec4f(t_vec4f vec4f);
void	print_ambient_info(t_ambient ambient);
void	print_sphere_info(t_sphere sphere);
void	print_plane_info(t_plane plane);
void	print_cylinder_info(t_cylinder cylinder);
void	print_camera_info(t_camera camera);
void	print_light_info(t_light light);
void	print_scene_data(t_scene_data data);

#endif