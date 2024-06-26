#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"
# include "color.h"

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
	t_color	color;
	float	brightness; // range 0.0-1.0
}	t_light;

typedef struct s_sphere
{
	t_vec4f	location;
	float	radius;
	float	diameter;
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
	t_color	color;
}	t_cylinder;

typedef enum e_objectid
{
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

typedef t_vec4f (*t_get_color)(void *object);


typedef struct s_object
{
	t_objectid		type;
	void			*object;
	print_data		print_object_data;
	t_get_location	get_location;
	t_get_color		get_color;
	intersect_ptr	intersect;
	struct s_object	*next;
}	t_object;

t_object	*new_object(t_objectid id, void *object);
t_object	*last_object(t_object *head);
void		append_object(t_object **head, t_object *object);
void		clear_objects(t_object *current);
void		object_removetype(t_object **head, t_objectid type);

#endif