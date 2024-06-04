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

int	check_format_object(char *line, t_rtobject id_count[ID_COUNT])
{
	char		**split;
	t_rtobject	identifier;

	if (line[0] == '\n')
		return (1);
	split = ft_split_charset(line, " \t\v\f\r\n");
	if (!split)
		return (perror("malloc error"), -1);
	id_count[identifier]++;
}

void	objects_to_scene_data(t_scene_data *scene, t_parse_object *objects, \
								t_rtobject id_count[ID_COUNT])
{

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

int	parse_rgb(const char *rgb)
{

}

int	parse_ambient(t_list **head, const char **format)
{
	t_ambient	*ambient;
	t_list		*new;

	if (arg_count(format) != 2)
		return (0);
	ambient = malloc(sizeof(*ambient));
	if (!ambient)
		return (0);
	ambient->ratio = ft_atof();
	new = ft_lstnew(ambient);
	if (!new)
		return (free(ambient), 0);
	ft_lstadd_back(head, new);
	return (1);
}

int	parse_object(const char *line, t_rtobject id_count[ID_COUNT], t_list **head)
{
	char		**split;
	int			ret;
	t_rtobject	id;

	id = check_identifier(line);
	if (id == INVALID)
		return (0);
	id_count[id]++;
	split = ft_split_charset(line, " \t\v\f\r\n");
	if (!split)
		return (perror("malloc error"), 0);
	if (id == AMBIENT)
		ret = parse_ambient(head, split + 1);
	else if (id == CAMERA)
		ret = parse_camera(head, split + 1);
	else if (id == LIGHT)
		ret = parse_light(head, split + 1);
	else if (id == SPHERE)
		ret = parse_sphere(head, split + 1);
	else if (id == PLANE)
		ret = parse_plane(head, split + 1);
	else if (id == CYLINDER)
		ret = parse_cylinder(head, split + 1);
	free_2d_array(split);
	return (ret);
}

int	parse_rt_file(t_scene_data *scene, int fd)
{
	char		*line;
	t_rtobject	id_count[ID_COUNT];
	t_list		*objects;

	ft_bzero(id_count, ID_COUNT);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (!parse_object(line, id_count, objects))
				return (free(line), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (id_count[AMBIENT] == 0 || id_count[CAMERA] == 0)
		return (0);
	objects_to_scene_data(scene, objects, id_count);
	return (1);
}
