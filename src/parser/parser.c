#include "parser.h"
#include "libft.h"
#include "get_next_line.h"

t_objectid	check_identifier(const char *id)
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
		fprintf(stderr, "Error: %s: invalid identifier.\n", split[0]);
		ft_free_2darray(split);
		return (0);
	}
	obj_count[type]++;
	ret = handle_object_type(objects, type, split + 1);
	ft_free_2darray(split);
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

static void	clear_gnl_buffer(int fd)
{
	char	*line;

	line = get_next_line(fd);

	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	parse_rt_file(t_scene_data *scene, int fd)
{
	char		*line;
	t_object	*objects;

	ft_bzero(scene->obj_count, sizeof(scene->obj_count));
	objects = NULL;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (!parse_object(line, scene->obj_count, &objects))
				return (clear_objects(objects), free(line), clear_gnl_buffer(fd), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!is_valid_object_count(scene->obj_count[AMBIENT], AMBIENT))
		return (clear_objects(objects), 0);
	if (!is_valid_object_count(scene->obj_count[CAMERA], CAMERA))
		return (clear_objects(objects), 0);
	if (!is_valid_object_count(scene->obj_count[LIGHT], LIGHT))
		return (clear_objects(objects), 0);
	objects_to_scene_data(scene, objects);
	clear_objects(objects);
	return (1);
}
