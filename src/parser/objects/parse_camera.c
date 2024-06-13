#include <stdio.h>
#include "libft.h"
#include "parser.h"

static int	has_valid_ranges(t_camera *camera)
{
	if (!ft_vec_in_range(camera->orientation, -1, 1))
	{
		fprintf(stderr, "Error: camera orientation \
vector out of range [-1, 1]\n");
		return (0);
	}
	if (camera->fov < 0 || camera->fov > 180)
	{
		fprintf(stderr, "Error: %d: camera fov \
out of range [0, 180]\n", camera->fov);
		return (0);
	}
	return (1);
}

int	parse_camera(t_object **objects, char **format)
{
	t_camera	*camera;
	t_object	*new;

	if (ft_2darray_size(format) != 3)
	{
		fprintf(stderr, "Error: incorrect camera info format.\n");
		return (0);
	}
	camera = malloc(sizeof(*camera));
	if (!camera)
		return (perror("malloc error"), 0);
	camera->location = atovec3f(format[0]);
	// printf("data camara in parse_camera: x, y, z %f %f %f\n", camera->location[0], camera->location[1], camera->location[2]);


	camera->orientation = atovec3f(format[1]);
	camera->fov = ft_atoi(format[2]);
	if (!has_valid_ranges(camera))
		return (free(camera), 0);
	new = new_object(CAMERA, camera);
	if (!new)
		return (perror("malloc error"), free(camera), 0);
	append_object(objects, new);
	return (1);
}
