#include "parser.h"
#include "libft.h"

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
	free(line);
	identifier = check_identifier(split[0]);
	if (identifier == INVALID)
		return (free_2d_array(split), 0);
	id_count[identifier]++;
}

int	parse_rt_file(int fd)
{
	char		*line;
	int			ret;
	t_rtobject	id_count[ID_COUNT];

	ft_bzero(id_count, sizeof(id_count));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (check_format_object(line, id_count) == -1)
			return (-1);
	}
	if (ret == -1)
		return (perror("get_next_line error"), -1);
	return (0);
}
