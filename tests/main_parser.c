#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "parser.h"
#include "debug_info.h"

static void	cleanup_scene_data(t_scene_data *scene)
{
	if (scene->sphere)
		free(scene->sphere);
	if (scene->plane)
		free(scene->plane);
	if (scene->cylinder)
		free(scene->cylinder);
}

int	main(int argc, char **argv)
{
	t_scene_data	scene;
	int				fd;

	if (argc != 2)
	{
		printf("Usage: %s examplefile.rt\n", argv[0]);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror(argv[1]), 1);
	if (!ft_str_endswith(argv[1], ".rt"))
	{
		fprintf(stderr, "Error: %s: not an .rt file.\n", argv[1]);
		close(fd);
		return (1);
	}
	else if (!parse_rt_file(&scene, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	print_scene_data(scene);
	cleanup_scene_data(&scene);
	return (0);
}
