#include <stdio.h>
#include <fcntl.h>
#include "minirt.h"
#include "parser.h"

static int	exit_error(int code, int fd, const char *arg)
{
	if (code == 0)
		printf("Usage: %s examplefile.rt\n", arg);
	else if (code == 1)
		fprintf(stderr, "Error: %s: not an .rt file.\n", arg);
	if (code != 0 && fd != -1)
		close(fd);
	return (code);
}

static void	init_scene_data(t_scene_data *scene)
{
	ft_bzero(scene->obj_count, sizeof(*scene->obj_count) * OBJ_COUNT);
	ft_bzero(&scene->ambient, sizeof(scene->ambient));
	ft_bzero(&scene->camera, sizeof(scene->camera));
	ft_bzero(&scene->light, sizeof(scene->light));
	scene->objects = NULL;
}

void apply_rodrigues_formula(t_scene_data *scene)
{
	const t_vec4f reference_vector = {1,0,0,1};
	t_vec4f cross_vector = cross_product(reference_vector, scene->camera.orientation);
	normalize_vector(&cross_vector);
	float angle = acosf(dot_product_3d(reference_vector, scene->camera.orientation) / (get_magnitude(reference_vector) * get_magnitude(scene->camera.orientation)));
	
	init_identy_matrix(scene->camera.rotation_comp);
	if (angle == (float)0)
		return;
	t_vec4f K[3] = {(t_vec4f){0, -cross_vector[2], cross_vector[1]},
				(t_vec4f){cross_vector[2], 0, -cross_vector[0]},
				(t_vec4f){-cross_vector[1], cross_vector[0], 0}};

	t_vec4f K_sin_theta[3];
	copy_matrix(K_sin_theta, K);
	scale_3x3_matrix(K_sin_theta, sinf(angle));

	t_vec4f K_squared_and_cos[3];
	matrix_multiply_3x3_3x3(K, K, K_squared_and_cos);
	scale_3x3_matrix(K_squared_and_cos, 1 - cosf(angle));

	matrix_addition(scene->camera.rotation_comp, K_sin_theta);
	matrix_addition(scene->camera.rotation_comp, K_squared_and_cos);	
}

void init_camera_rotation(t_scene_data *scene)
{
	apply_rodrigues_formula(scene);
	init_identy_matrix(scene->camera.rotation_around_y);
	init_identy_matrix(scene->camera.rotation_around_z);
}

int	main(int argc, char **argv)
{
	t_scene_data	scene;
	int				fd;

	if (argc != 2)
		return (exit_error(0, -1, argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror(argv[1]), 1);
	init_scene_data(&scene);
	if (!ft_str_endswith(argv[1], ".rt"))
		return (exit_error(1, fd, argv[1]));
	else if (!parse_rt_file(&scene, fd))
		return (exit_error(2, fd, NULL));
	close(fd);
	init_camera_rotation(&scene);
	render_scene(&scene);
	clear_objects(scene.objects);
	return (0);
}
