#ifndef PARSER_H
# define PARSER_H
# define OBJ_COUNT 6
# include <stdlib.h>

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

typedef struct s_object
{
	t_objectid		type;
	void			*object;
	struct s_object	*next;
}	t_object;

typedef struct s_scene_data
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
	int			obj_count[OBJ_COUNT];
}	t_scene_data;

t_object	*new_object(t_objectid id, void *object);
t_object	*last_object(t_object *head);
void		append_object(t_object **head, t_object *object);
void		clear_objects(t_object *current);

float		ft_atof(const char *s);
char		**ft_split_charset(const char *s, const char *set);
size_t		ft_chcount(const char *s, const char c);
int			parse_rt_file(t_scene_data *scene, int fd);
char		*ft_str_endswith(const char *s, const char *end);
#endif