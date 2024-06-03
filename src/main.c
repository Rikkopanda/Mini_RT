#include <stdio.h>
#include "libft.h"
#define ID_COUNT 6

char	**ft_split_charset(const char *s, const char *set);
typedef float t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));

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

t_rtobject	check_identifier(const char *id)
{
	unsigned int	len;

	len = ft_strlen(id);
	if (!ft_strncmp("A", id, len))
		return (AMBIENT);
	else if (!ft_strncmp("C", id, len))
		return (CAMERA);
	else if (!ft_strncmp("L", id, len))
		return (LIGHT);
	else if (!ft_strncmp("sp", id, len))
		return (SPHERE);
	else if (!ft_strncmp("pl", id, len))
		return (PLANE);
	else if (!ft_strncmp("cy", id, len))
		return (CYLINDER);
	return (INVALID);
}

void	free_2d_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	check_format_object(char *line, t_rtobject id_count[ID_COUNT])
{
	char		**split;
	t_rtobject	identifier;

	if (line[0] == '\n')
		return (1);
	split = ft_split_charset(line, " \t\v\f\r");
	if (!split)
		return (perror("malloc error"), -1);
	free(line);
	identifier = check_identifier(split[0]);
	if (identifier == INVALID)
		return (free_2d_array(split), 0);
	id_count[identifier]++;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s examplefile.rt\n", argv[0]);
		return (0);
	}
	return (0);
}
