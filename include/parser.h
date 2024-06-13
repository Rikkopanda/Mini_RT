#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>

# include "minirt.h"
// # include "objects.h"

// typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));
// 
// typedef struct s_object		t_object;
// typedef struct t_ambient	t_ambient;
// typedef struct s_camera		t_camera;
// typedef struct s_light		t_light;
// typedef struct s_ray		t_ray;
// typedef struct s_sphere		t_sphere;
// typedef struct s_win		t_win;
// typedef struct s_img		t_img;

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

int			parse_ambient(t_object **objects, char **format);
int			parse_camera(t_object **objects, char **format);
int			parse_light(t_object **objects, char **format);
int			parse_sphere(t_object **objects, char **format);
int			parse_plane(t_object **objects, char **format);
int			parse_cylinder(t_object **objects, char **format);
int			parse_object(const char *line, int obj_count[OBJ_COUNT], \
						t_object **objects);
int			parse_rt_file(t_scene_data *scene, int fd);

/* debug functions */
void		print_sphere_data(void *object);
void		print_camera_data(void *object);

#endif