#include "parser.h"


static t_objectid	check_identifier(const char *id)
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

static int	handle_object_type(t_object **objects, \
								t_objectid type, char **format)
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

int	parse_object(const char *line, int obj_count[OBJ_COUNT], t_object **objects)
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
