#include <stdio.h>
#include <fcntl.h>
#include "minirt.h"
#include "parser.h"
#include "libft.h"

void	test_file_extensions(void)
{
	char	*correct[] = {
		"test.rt",
		"validfile2.rt",
		"validfile.rt.rt",
		"validfile.rt.rt",
	};
	char	*incorrect[] = {
		"nonexistingfile",
		"notvalidextension.r",
		"notvalidextension2.rtt",
		"notvalidextension2.rrt",
		"notvalidextension3.rt.",
	};
	int 	files_correct = sizeof(correct) / sizeof(*correct);
	int 	files_incorrect = sizeof(incorrect) / sizeof(*incorrect);
	char	*output;

	for (int i = 0; i < files_correct; i++) {
		printf("input: %s\n", correct[i]);
		output = ft_str_endswith(correct[i], ".rt");
		if (output != NULL)
			printf("[OK]\n");
		else
			printf("[KO]\n");
	}
	for (int i = 0; i < files_incorrect; i++) {
		printf("input: %s\n", incorrect[i]);
		output = ft_str_endswith(incorrect[i], ".rt");
		if (output == NULL)
			printf("[OK]\n");
		else
			printf("[KO]\n");
	}
}

int	main(int argc, char **argv)
{
	t_scene_data	scene;
	int				fd;

	(void)argc;
	(void)argv;
	(void)scene;
	(void)fd;
	test_file_extensions();
	// fd = open(argv[1], O_RDONLY);
	// if (fd == -1)
	// 	return (perror(argv[1]), 1);
	// if (!parse_rt_file(&scene, fd))
	// {
	// 	close(fd);
	// 	return (1);
	// }
	return (0);
}
