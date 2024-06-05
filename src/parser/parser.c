#include "parser.h"
#include "libft.h"
#include "get_next_line.h"

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

t_objectid	check_identifier(const char *id)
{
	unsigned int	len;

	len = ft_strlen(id);
	if (!ft_strncmp("A", id, len))
		return ( AMBIENT);
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

void	init_shapes(t_scene_data *scene, int id_count[OBJ_COUNT])
{
	if (id_count[SPHERE] == 0)
		scene->sphere = NULL;
	else
		scene->sphere = malloc(id_count[SPHERE] * sizeof(*scene->sphere));
	if (id_count[PLANE] == 0)
		scene->plane = NULL;
	else
		scene->plane = malloc(id_count[PLANE] * sizeof(*scene->plane));
	if (id_count[CYLINDER] == 0)
		scene->cylinder = NULL;
	else
		scene->cylinder = malloc(id_count[CYLINDER] * sizeof(*scene->cylinder));
}

void	objects_to_scene_data(t_scene_data *scene, t_object *current)
{
	int	sphere_index;
	int	plane_index;
	int	cylinder_index;

	init_shapes(scene, scene->obj_count);
	sphere_index = scene->obj_count[SPHERE] - 1;
	plane_index = scene->obj_count[PLANE] - 1;
	cylinder_index = scene->obj_count[CYLINDER] - 1;
	while (current)
	{
		if (current->type == AMBIENT)
			scene->ambient = *(t_ambient *)current->object;
		else if (current->type == CAMERA)
			scene->camera = *(t_camera *)current->object;
		else if (current->type == LIGHT)
			scene->light = *(t_light *)current->object;
		else if (current->type == SPHERE)
			scene->sphere[sphere_index--] = *(t_sphere *)current->object;
		else if (current->type == PLANE)
			scene->plane[plane_index--] = *(t_plane *)current->object;
		else if (current->type == CYLINDER)
			scene->cylinder[cylinder_index--] = *(t_cylinder *)current->object;
		current = current->next;
	}
}

size_t	arg_count(char **args)
{
	size_t	count;

	if (!args)
		return (0);
	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	rgb_to_hex(int r, int g, int b)
{
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255)
		return (0);
	return ((r << 16) | (g << 8) | b);
}

int	ft_atohex(const char *a_rgb)
{
	char	**split;
	int		rgb[3];

	split = ft_split(a_rgb, ',');
	if (!split)
		return (perror("malloc error"), 0);
	if (arg_count(split) != 3)
		return (free_2d_array(split), 0);
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	free_2d_array(split);
	return (rgb_to_hex(rgb[0], rgb[1], rgb[2]));
}

t_vec4f	atovec3f(const char *a_vec3f)
{
	t_vec4f	vec4;
	char	**split;

	split = ft_split(a_vec3f, ',');
	if (!split)
		return (perror("malloc error"), (t_vec4f){0,0,0,0});
	if (arg_count(split) != 3)
		return (free_2d_array(split), (t_vec4f){0,0,0,0});
	vec4[0] = ft_atof(split[0]);
	vec4[1] = ft_atof(split[1]);
	vec4[2] = ft_atof(split[2]);
	vec4[3] = 0;
	free_2d_array(split);
	return (vec4);
}

int	parse_ambient(t_object **head, char **format)
{
	t_ambient	*ambient;
	t_object	*new;

	// fprintf(stderr, "parsing ambient\n");
	if (arg_count(format) != 2)
		return (0);
	ambient = malloc(sizeof(*ambient));
	if (!ambient)
		return (perror("malloc error"), 0);
	ambient->ratio = ft_atof(format[0]);
	if (ambient->ratio < 0.0f || ambient->ratio > 1.0f)
	{
		fprintf(stderr, "Error: %.2f: ambient lighting ratio out of range [0.0, 1.0]\n", ambient->ratio);
		return (free(ambient), 0);
	}
	ambient->hexcolor = ft_atohex(format[1]);
	new = new_object(AMBIENT, ambient);
	if (!new)
		return (perror("malloc error"), free(ambient), 0);
	append_object(head, new);
	return (1);
}

int	parse_camera(t_object **head, char **format)
{
	t_camera	*camera;
	t_object	*new;

	// fprintf(stderr, "parsing camera\n");
	if (arg_count(format) != 3)
		return (0);
	camera = malloc(sizeof(*camera));
	if (!camera)
		return (perror("malloc error"), 0);
	camera->location = atovec3f(format[0]);
	camera->orientation = atovec3f(format[1]);
	if (camera->orientation[0] < -1 || camera->orientation[0] > 1 ||
		camera->orientation[1] < -1 || camera->orientation[1] > 1 ||
		camera->orientation[2] < -1 || camera->orientation[2] > 1)
	{
		fprintf(stderr, "Error: camera orientation vector out of range [-1, 1]\n");
		return (free(camera), 0);
	}
	camera->fov = ft_atoi(format[2]);
	if (camera->fov < 0 || camera->fov > 180)
	{
		fprintf(stderr, "Error: %d: camera fov out of range [0, 180]\n", camera->fov);
		return (free(camera), 0);
	}
	new = new_object(CAMERA, camera);
	if (!new)
		return (perror("malloc error"), free(camera), 0);
	append_object(head, new);
	return (1);
}

int	parse_light(t_object **head, char **format)
{
	t_light		*light;
	t_object	*new;

	// fprintf(stderr, "parsing light\n");
	if (arg_count(format) != 3)
		return (0);
	light = malloc(sizeof(*light));
	if (!light)
		return (perror("malloc error"), 0);
	light->location = atovec3f(format[0]);
	light->ratio = ft_atof(format[1]);
	if (light->ratio < 0.0f || light->ratio > 1.0f)
	{
		fprintf(stderr, "Error: %.2f: light brightness ratio out of range [0.0, 1.0]\n", light->ratio);
		return (free(light), 0);
	}
	light->hexcolor = 0xFFFFFF;
	new = new_object(LIGHT, light);
	if (!new)
		return (perror("malloc error"), free(light), 0);
	append_object(head, new);
	return (1);
}

int	parse_sphere(t_object **head, char **format)
{
	t_sphere	*sphere;
	t_object	*new;

	// fprintf(stderr, "parsing sphere\n");
	if (arg_count(format) != 3)
		return (0);
	sphere = malloc(sizeof(*sphere));
	if (!sphere)
		return (perror("malloc error"), 0);
	sphere->location = atovec3f(format[0]);
	sphere->diameter = ft_atof(format[1]);
	sphere->hexcolor = ft_atohex(format[2]);
	new = new_object(SPHERE, sphere);
	if (!new)
		return (perror("malloc error"), free(sphere), 0);
	append_object(head, new);
	return (1);
}

int	parse_plane(t_object **head, char **format)
{
	t_plane		*plane;
	t_object	*new;

	// fprintf(stderr, "parsing plane\n");
	if (arg_count(format) != 3)
		return (0);
	plane = malloc(sizeof(*plane));
	if (!plane)
		return (perror("malloc error"), 0);
	plane->location = atovec3f(format[0]);
	plane->vector = atovec3f(format[1]);
	if (plane->vector[0] < -1 || plane->vector[0] > 1 ||
		plane->vector[1] < -1 || plane->vector[1] > 1 ||
		plane->vector[2] < -1 || plane->vector[2] > 1)
	{
		fprintf(stderr, "Error: plane normal vector out of range [-1, 1]\n");
		return (free(plane), 0);
	}
	plane->hexcolor = ft_atohex(format[2]);
	new = new_object(PLANE, plane);
	if (!new)
		return (perror("malloc error"), free(plane), 0);
	append_object(head, new);
	return (1);
}

int	parse_cylinder(t_object **head, char **format)
{
	t_cylinder	*cylinder;
	t_object	*new;

	// fprintf(stderr, "parsing cylinder\n");
	if (arg_count(format) != 5)
		return (0);
	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
		return (perror("malloc error"), 0);
	cylinder->location = atovec3f(format[0]);
	cylinder->vector = atovec3f(format[1]);
	if (cylinder->vector[0] < -1 || cylinder->vector[0] > 1 ||
		cylinder->vector[1] < -1 || cylinder->vector[1] > 1 ||
		cylinder->vector[2] < -1 || cylinder->vector[2] > 1)
	{
		fprintf(stderr, "Error: cylinder normal vector out of range [-1, 1]\n");
		return (free(cylinder), 0);
	}
	cylinder->diameter = ft_atof(format[2]);
	cylinder->height = ft_atof(format[3]);
	cylinder->hexcolor = ft_atohex(format[4]);
	new = new_object(CYLINDER, cylinder);
	if (!new)
		return (perror("malloc error"), free(cylinder), 0);
	append_object(head, new);
	return (1);
}

static int	handle_object_type(t_object **objects, t_objectid type, char **format)
{
	if (type == AMBIENT)
		return (parse_ambient(objects, format));
	else if (type == CAMERA)
		return (parse_camera(objects, format));
	else if (type == LIGHT)
		return (parse_light(objects, format));
	else if (type == SPHERE)
		return (parse_sphere(objects, format));
	else if (type == PLANE)
		return (parse_plane(objects, format));
	else if (type == CYLINDER)
		return (parse_cylinder(objects, format));
	return (0);
}

static int	parse_object(const char *line, int obj_count[OBJ_COUNT], t_object **objects)
{
	char		**split;
	int			ret;
	t_objectid	type;

	split = ft_split_charset(line, " \t\v\f\r\n");
	if (!split)
		return (perror("malloc error"), 0);
	type = check_identifier(split[0]);
	if (type == INVALID)
	{
		free_2d_array(split);
		fprintf(stderr, "Error: %s: invalid identifier.\n", split[0]);
		return (0);
	}
	obj_count[type]++;
	ret = handle_object_type(objects, type, split + 1);
	free_2d_array(split);
	return (ret);
}

static int	is_valid_object_count(int count, t_objectid type)
{
	if (count == 1)
		return (1);
	if (count == 0)
		fprintf(stderr, "Error: missing ");
	else if (count > 1)
		fprintf(stderr, "Error: too many ");
	if (type == AMBIENT)
		fprintf(stderr, "ambient element(s).\n");
	else if (type == CAMERA)
		fprintf(stderr, "camera object(s).\n");
	else if (type == LIGHT)
		fprintf(stderr, "light object(s).\n");
	return (0);
}

int	parse_rt_file(t_scene_data *scene, int fd)
{
	char		*line;
	t_object	*objects;

	ft_bzero(scene->obj_count, OBJ_COUNT * sizeof(int));
	objects = NULL;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (!parse_object(line, scene->obj_count, &objects))
				return (clear_objects(objects), free(line), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!is_valid_object_count(scene->obj_count[AMBIENT], AMBIENT))
		return (0);
	if (!is_valid_object_count(scene->obj_count[CAMERA], CAMERA))
		return (0);
	if (!is_valid_object_count(scene->obj_count[LIGHT], LIGHT))
		return (0);
	objects_to_scene_data(scene, objects);
	clear_objects(objects);
	return (1);
}
