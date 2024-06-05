#ifndef PARSER_H
# define PARSER_H
# define OBJ_COUNT 6
# include <stdlib.h>
# include "objects.h"
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
	struct s_object	*next;
}	t_object;

typedef struct s_scene_data
{
	int			obj_count[OBJ_COUNT];
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
}	t_scene_data;

t_object	*new_object(t_objectid id, void *object);
t_object	*last_object(t_object *head);
void		append_object(t_object **head, t_object *object);
void		clear_objects(t_object *current);

/* parser lib functions */
int			ft_min(int a, int b);
int			ft_max(int a, int b);
float		ft_atof(const char *s);
int			ft_atohex(const char *a_rgb);
t_vec4f		atovec3f(const char *a_vec3f);
int			clamped_rgb_to_hex(int r, int g, int b);
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
int			parse_rt_file(t_scene_data *scene, int fd);
#endif