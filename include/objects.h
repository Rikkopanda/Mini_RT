#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"
# include "color.h"

#define STATUS_INDEX 3

typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));
// typedef struct s_color	t_color;

typedef struct s_ray
{
	t_vec4f	origin;
	t_vec4f	direction;
} t_ray;

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
	float	smoothness;
	float	brightness; // range 0.0-1.0
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

typedef void (*print_data)(void *object);

typedef t_vec4f (*intersect_ptr)(void *object, t_ray ray);

typedef t_vec4f (*t_get_location)(void *object);

typedef void (*t_set_location)(void *object, int xyz_index, int addition);

typedef t_vec4f (*t_get_color)(void *object);

typedef t_vec4f (*t_get_normal)(void *object, t_vec4f point);

typedef float (*t_get_smoothness)(void *object);

typedef float (*t_get_brightness)(void *object);

typedef struct s_object
{
	t_objectid			type;
	void				*object;
	print_data			print_object_data;
	t_get_location		get_location;
	t_set_location		set_location;
	t_get_color			get_color;
	t_get_normal		get_normal;
	t_get_smoothness	get_smoothness;
	t_get_brightness	get_brightness;
	intersect_ptr		intersect;
	struct s_object		*next;
}	t_object;

t_object	*new_object(t_objectid id, void *object);
t_object	*last_object(t_object *head);
void		append_object(t_object **head, t_object *object);
void		clear_objects(t_object *current);
void		object_removetype(t_object **head, t_objectid type);

t_vec4f 	get_location_sphere(void *object);
t_vec4f		get_color_sphere(void *object);
float		get_smoothness_sphere(void *object);
void		set_location_sphere(void *object, int xyz_index, int addition);

t_vec4f 	get_location_light(void *object);
t_vec4f		get_color_light(void *object);
float		get_brightness_light(void *object);
void		set_location_light(void *object, int xyz_index, int addition);


#endif