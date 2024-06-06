#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include "objects.h"

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

/* parser lib functions */
int			ft_min(int a, int b);
int			ft_max(int a, int b);
float		ft_atof(const char *s);
int			ft_atohex(const char *a_rgb);
t_vec4f		atovec3f(const char *a_vec3f);
int			ft_vec_in_range(t_vec4f vec4f, float low, float high);
int			clamped_rgb_to_hex(int r, int g, int b);
char		**ft_split_charset(const char *s, const char *set);
char		*ft_str_endswith(const char *s, const char *end);
size_t		ft_2darray_size(char **arr);
void		ft_free_2darray(char **array);
void		cleanup_scene_data(t_scene_data *scene);

int			parse_rt_file(t_scene_data *scene, int fd);
#endif