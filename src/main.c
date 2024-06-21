#include <stdio.h>
#include <fcntl.h>
#include "minirt.h"
#include "parser.h"
#include "minirt.h"

static int	exit_error(int code, int fd, const char *arg)
{
	if (code == 0)
	{
		printf("Usage: %s maps/[..]/examplefile.rt\n", arg);
		printf("Window dimensions: %s maps/[..]/examplefile.rt 1920 1080\n", arg);
	}
	else if (code == 1)
		fprintf(stderr, "Error: %s: invalid window dimension.\n", arg);
	else if (code == 2)
		fprintf(stderr, "Error: %s: not an .rt file.\n", arg);
	if (code != 0 && fd != -1)
		close(fd);
	return (code);
}

static void	init_scene_data(t_scene_data *scene)
{
	ft_bzero(scene->obj_count, sizeof(*scene->obj_count) * OBJ_TYPE_COUNT);
	ft_bzero(&scene->ambient, sizeof(scene->ambient));
	ft_bzero(&scene->camera, sizeof(scene->camera));
	ft_bzero(&scene->light, sizeof(scene->light));
	scene->win_height = WINDOW_HEIGHT;
	scene->win_width = WINDOW_WIDTH;
	scene->objects = NULL;
}

int	main(int argc, char **argv)
{
	t_scene_data	scene;
	int				fd;

	if (argc != 2 && argc != 4)
		return (exit_error(0, -1, argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror(argv[1]), 1);
	init_scene_data(&scene);
	if (argc == 4)
	{
		scene.win_width = ft_atoi(argv[2]);
		scene.win_height = ft_atoi(argv[3]);
		if (scene.win_width <= 0 || scene.win_width > 3840)
			return (exit_error(1, fd, argv[2]));
		if (scene.win_height <= 0 || scene.win_height > 2160)
			return (exit_error(1, fd, argv[3]));
	}
	if (!ft_str_endswith(argv[1], ".rt"))
		return (exit_error(2, fd, argv[1]));
	else if (!parse_rt_file(&scene, fd))
		return (exit_error(3, fd, NULL));
	close(fd);
	render_scene(&scene);
	clear_objects(scene.objects);
	return (0);
}
