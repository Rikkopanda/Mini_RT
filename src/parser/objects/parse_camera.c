#include <stdio.h>
#include "libft.h"
#include "parser.h"

int	parse_camera(t_object **objects, char **format)
{
	t_camera	*camera;
	t_object	*new;

	// fprintf(stderr, "parsing camera\n");
	if (ft_2darray_size(format) != 3)
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
	append_object(objects, new);
	return (1);
}
