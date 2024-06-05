#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "parser.h"

int	main(int argc, char **argv)
{
	t_scene_data	scene;
	int				fd;

	if (argc != 2)
	{
		printf("Usage: %s examplefile.rt\n", argv[0]);
		return (0);
	}
	if (!ft_str_endswith(argv[1], ".rt"))
	{
		printf("Error: %s: not an .rt file.\n", argv[1]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror(argv[1]), 1);
	if (!parse_rt_file(&scene, fd))
	{
		close(fd);
		return (1);
	}
	return (0);
}
