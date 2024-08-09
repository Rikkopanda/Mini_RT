/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 15:23:24 by kwchu         #+#    #+#                 */
/*   Updated: 2024/08/09 17:32:46 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"
# include "color.h"

# define STATUS_INDEX 3

typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));

typedef struct s_ray
{
	t_vec4f	origin;
	t_vec4f	direction;
}	t_ray;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec4f	location;
	t_vec4f	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec4f	location;
	float	ratio;
	float	diameter;
	float	radius;
	t_color	color;
	float	brightness;
}	t_light;

typedef struct s_sphere
{
	t_vec4f	location;
	float	radius;
	float	diameter;
	float	smoothness;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec4f	location;
	t_vec4f	vector;
	float	smoothness;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec4f	location;
	t_vec4f	vector;
	float	diameter;
	float	radius;
	float	height;
	float	smoothness;
	t_color	color;
}	t_cylinder;

typedef enum e_objectid
{
	NONE = -2,
	INVALID = -1,
	AMBIENT = 0,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	OBJ_TYPE_COUNT,
}	t_objectid;

typedef void	(*t_print_data)(void *object);

typedef t_vec4f	(*t_intersect)(void *object, t_ray ray);

typedef t_vec4f	(*t_get_location)(void *object);

typedef void	(*t_set_location)(void *object, int xyz_index, int addition);

typedef t_vec4f	(*t_get_color)(void *object);

typedef t_vec4f	(*t_get_normal)(void *object, t_vec4f point);

typedef float	(*t_get_smoothness)(void *object);

typedef float	(*t_get_brightness)(void *object);

typedef struct s_object
{
	t_objectid			type;
	void				*object;
	t_print_data		print_object_data;
	t_get_location		get_location;
	t_set_location		set_location;
	t_get_color			get_color;
	t_get_normal		get_normal;
	t_get_smoothness	get_smoothness;
	t_get_brightness	get_brightness;
	t_intersect			intersect;
	struct s_object		*next;
}	t_object;

typedef struct s_sphere_intersect
{
	float	perpendicular_point;
	float	pp_distance;
	float	radius_squared;
}	t_sphere_intersect;

typedef struct s_cylinder_intersect
{
	t_vec4f	top_center;
	t_vec4f	bottom_center;
	float	a;
	float	b;
	float	d_dot_v;
	float	t1;
	float	t2;
	float	t_top;
	float	t_bottom;
	float	t_min;
}	t_cylinder_intersect;

t_object	*new_object(t_objectid id, void *object);
t_object	*last_object(t_object *head);
void		append_object(t_object **head, t_object *object);
void		clear_objects(t_object *current);
void		object_removetype(t_object **head, t_objectid type);

t_vec4f		intersect_light(void *object, t_ray ray);
t_vec4f		intersect_sphere(void *object, t_ray ray);
t_vec4f		intersect_plane(void *object, t_ray ray);
t_vec4f		intersect_cylinder(void *object, t_ray ray);

void		print_sphere_data(void *object);
void		print_cylinder_data(void *object);
void		print_plane_data(void *object);
void		print_camera_data(void *object);
void		print_light_data(void *object);

t_vec4f		get_location_sphere(void *object);
t_vec4f		get_color_sphere(void *object);
float		get_smoothness_sphere(void *object);
void		set_location_sphere(void *object, int xyz_index, int addition);
t_vec4f		get_normal_sphere(void *object, t_vec4f point);

t_vec4f		get_location_plane(void *object);
t_vec4f		get_color_plane(void *object);
float		get_smoothness_plane(void *object);
void		set_location_plane(void *object, int xyz_index, int addition);
t_vec4f		get_normal_plane(void *object, t_vec4f point);

t_vec4f		get_location_cylinder(void *object);
t_vec4f		get_color_cylinder(void *object);
float		get_smoothness_cylinder(void *object);
void		set_location_cylinder(void *object, int xyz_index, int addition);
t_vec4f		get_normal_cylinder(void *object, t_vec4f point);

t_vec4f		get_location_light(void *object);
t_vec4f		get_color_light(void *object);
float		get_brightness_light(void *object);
void		set_location_light(void *object, int xyz_index, int addition);

void		assign_intersect(t_object *object);
void		assign_location_getter(t_object *object);
void		assign_location_setter(t_object *object);
void		assign_normal_getter(t_object *object);

void		assign_color_getter(t_object *object);
void		assign_smoothness_getter(t_object *object);
void		assign_brightness_getter(t_object *object);

#endif