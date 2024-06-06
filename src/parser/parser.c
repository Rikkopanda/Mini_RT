#include "parser.h"
#include "libft.h"
#include "get_next_line.h"

static int	init_shapes(t_scene_data *scene, int id_count[OBJ_COUNT])
{
	if (id_count[SPHERE] != 0)
	{
		scene->sphere = malloc(id_count[SPHERE] * sizeof(*scene->sphere));
		if (!scene->sphere)
			return (0);
	}
	if (id_count[PLANE] != 0)
	{
		scene->plane = malloc(id_count[PLANE] * sizeof(*scene->plane));
		if (!scene->plane)
			return (0);
	}
	if (id_count[CYLINDER] != 0)
	{
		scene->cylinder = malloc(id_count[CYLINDER] * sizeof(*scene->cylinder));
		if (!scene->cylinder)
			return (0);
	}
	return (1);
}

static void	objects_to_scene_data(t_scene_data *scene, t_object *current)
{
	int	sphere_index;
	int	plane_index;
	int	cylinder_index;

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

static int	is_valid_scene(t_scene_data *scene)
{
	if (!is_valid_object_count(scene->obj_count[AMBIENT], AMBIENT) || \
		!is_valid_object_count(scene->obj_count[CAMERA], CAMERA) || \
		!is_valid_object_count(scene->obj_count[LIGHT], LIGHT))
		return (0);
	if (!init_shapes(scene, scene->obj_count))
		return (0);
	return (1);
}

/* calling get_next_line with -1 as fd flushes buffer if its not empty */

int	parse_rt_file(t_scene_data *scene, int fd)
{
	char		*line;
	t_object	*objects;

	objects = NULL;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (!parse_object(line, scene->obj_count, &objects))
			{
				get_next_line(-1);
				return (clear_objects(objects), free(line), 0);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!is_valid_scene(scene))
		return (cleanup_scene_data(scene), clear_objects(objects), 0);
	objects_to_scene_data(scene, objects);
	clear_objects(objects);
	return (1);
}
