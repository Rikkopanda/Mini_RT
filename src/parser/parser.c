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
	char			**split;

	split = ft_split_charset(id, " \t\v\f\r\n");
	len = ft_strlen(split[0]);
	if (!ft_strncmp("A", split[0], len))
		return (free_2d_array(split), AMBIENT);
	else if (!ft_strncmp("C", split[0], len))
		return (free_2d_array(split), CAMERA);
	else if (!ft_strncmp("L", split[0], len))
		return (free_2d_array(split), LIGHT);
	else if (!ft_strncmp("sp", split[0], len))
		return (free_2d_array(split), SPHERE);
	else if (!ft_strncmp("pl", split[0], len))
		return (free_2d_array(split), PLANE);
	else if (!ft_strncmp("cy", split[0], len))
		return (free_2d_array(split), CYLINDER);
	return (free_2d_array(split), INVALID);
}

// void	objects_to_scene_data(t_scene_data *scene, t_object *objects, \
// 								t_objectid id_count[OBJ_COUNT])
// {
	
// }

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

	fprintf(stderr, "parsing ambient\n");
	if (arg_count(format) != 2)
		return (0);
	ambient = malloc(sizeof(*ambient));
	if (!ambient)
		return (perror("malloc error"), 0);
	ambient->ratio = ft_atof(format[0]);
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

	fprintf(stderr, "parsing camera\n");
	if (arg_count(format) != 3)
		return (0);
	camera = malloc(sizeof(*camera));
	if (!camera)
		return (perror("malloc error"), 0);
	camera->location = atovec3f(format[0]);
	camera->orientation = atovec3f(format[1]);
	camera->fov = ft_atoi(format[2]);
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

	fprintf(stderr, "parsing light\n");
	if (arg_count(format) != 3)
		return (0);
	light = malloc(sizeof(*light));
	if (!light)
		return (perror("malloc error"), 0);
	light->location = atovec3f(format[0]);
	light->ratio = ft_atof(format[1]);
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

	fprintf(stderr, "parsing sphere\n");
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

	fprintf(stderr, "parsing plane\n");
	if (arg_count(format) != 3)
		return (0);
	plane = malloc(sizeof(*plane));
	if (!plane)
		return (perror("malloc error"), 0);
	plane->location = atovec3f(format[0]);
	plane->vector = atovec3f(format[1]);
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

	fprintf(stderr, "parsing cylinder\n");
	if (arg_count(format) != 5)
		return (0);
	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
		return (perror("malloc error"), 0);
	cylinder->location = atovec3f(format[0]);
	cylinder->vector = atovec3f(format[1]);
	cylinder->diameter = ft_atof(format[2]);
	cylinder->height = ft_atof(format[3]);
	cylinder->hexcolor = ft_atohex(format[4]);
	new = new_object(CYLINDER, cylinder);
	if (!new)
		return (perror("malloc error"), free(cylinder), 0);
	append_object(head, new);
	return (1);
}

int	parse_object(const char *line, t_objectid obj_count[OBJ_COUNT], t_object **head)
{
	char		**split;
	int			ret;
	t_objectid	type;

	type = check_identifier(line);
	if (type == INVALID)
		return (0);
	obj_count[type]++;
	split = ft_split_charset(line, " \t\v\f\r\n");
	if (!split)
		return (perror("malloc error"), 0);
	if (type == AMBIENT)
		ret = parse_ambient(head, split + 1);
	else if (type == CAMERA)
		ret = parse_camera(head, split + 1);
	else if (type == LIGHT)
		ret = parse_light(head, split + 1);
	else if (type == SPHERE)
		ret = parse_sphere(head, split + 1);
	else if (type == PLANE)
		ret = parse_plane(head, split + 1);
	else if (type == CYLINDER)
		ret = parse_cylinder(head, split + 1);
	else
		ret = 0;
	free_2d_array(split);
	return (ret);
}

void	print_object_types(t_object *objects)
{
	while (objects)
	{
		printf("%d\n", objects->type);
		objects = objects->next;
	}
}

int	parse_rt_file(t_scene_data *scene, int fd)
{
	char		*line;
	t_objectid	obj_count[OBJ_COUNT];
	t_object	*objects;

	ft_bzero(obj_count, OBJ_COUNT);
	objects = NULL;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (!parse_object(line, obj_count, &objects))
			{
				fprintf(stderr, "Error: could not parse object.\n");
				return (clear_objects(objects), free(line), 0);
			}
		}
		if (obj_count[CAMERA] > 1 || obj_count[AMBIENT] > 1)
			return (clear_objects(objects), free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (obj_count[AMBIENT] == 0 || obj_count[CAMERA] == 0)
		return (0);
	(void)scene;
	// objects_to_scene_data(scene, objects, obj_count);
	print_object_types(objects);
	clear_objects(objects);
	return (1);
}
