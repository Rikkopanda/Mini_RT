#ifndef OBJECTS_H
# define OBJECTS_H
# define OBJ_COUNT 6

typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));

typedef struct s_ray
{
	t_vec4f	normalized_vec;
	t_vec4f	scaled_vec;
	t_vec4f	world_pos_of_scaled_vec;
	float	step;
} t_ray;

typedef struct s_ambient
{
	float	ratio;
	int		hexcolor;
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
	int		hexcolor;
}	t_light;

typedef struct s_sphere
{
	t_vec4f	location;
	float	radius;
	float	diameter;
	int		hexcolor;
}	t_sphere;

typedef struct s_plane
{
	t_vec4f	location;
	t_vec4f	vector;
	int		hexcolor;
}	t_plane;

typedef struct s_cylinder
{
	t_vec4f	location;
	t_vec4f	vector;
	float	diameter;
	float	radius;
	float	height;
	int		hexcolor;
}	t_cylinder;

typedef enum e_objectid
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	INVALID,
}	t_objectid;

typedef struct s_object
{
	t_objectid		type;
	void			*object;
	const void		*intersect;
	struct s_object	*next;
}	t_object;

t_object	*new_object(t_objectid id, void *object);
t_object	*last_object(t_object *head);
void		append_object(t_object **head, t_object *object);
void		clear_objects(t_object *current);
void		object_removetype(t_object **head, t_objectid type);

#endif