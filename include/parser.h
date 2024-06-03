#ifndef PARSER_H
# define PARSER_H
# define ID_COUNT 6

typedef enum e_rtobject
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	INVALID,
}	t_rtobject;

typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));

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
	float	height;
	int		hexcolor;
}	t_cylinder;

typedef struct s_scene_data
{
	t_ambient	ambient;
	t_camera	*cameras;
	t_light		*lights;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
}	t_scene_data;
#endif