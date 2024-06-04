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

int	check_format_object(char *line, t_objectid id_count[OBJ_COUNT])
{
	char		**split;
	t_objectid	identifier;

	if (line[0] == '\n')
		return (1);
	split = ft_split_charset(line, " \t\v\f\r\n");
	if (!split)
		return (perror("malloc error"), -1);
	id_count[identifier]++;
}

void	objects_to_scene_data(t_scene_data *scene, t_object *objects, \
								t_objectid id_count[OBJ_COUNT])
{
	scene->cameras = 
}

size_t	arg_count(const char **args)
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

int	ft_atorgb(const char *a_rgb)
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

int	parse_ambient(t_object **head, const char **format)
{
	t_ambient	*ambient;
	t_object	*new;

	if (arg_count(format) != 2)
		return (0);
	ambient = malloc(sizeof(*ambient));
	if (!ambient)
		return (perror("malloc error"), 0);
	ambient->ratio = ft_atof(format[0]);
	ambient->hexcolor = ft_atorgb(format[1]);
	new = new_object(AMBIENT, ambient);
	if (!new)
		return (perror("malloc error"), free(ambient), 0);
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
	free_2d_array(split);
	return (ret);
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
			if (!parse_object(line, obj_count, objects))
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
	objects_to_scene_data(scene, objects, obj_count);
	clear_objects(objects);
	return (1);
}
