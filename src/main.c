#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "parser.h"

void	print_vec4f(t_vec4f vec4f)
{
	printf("(%.2f, %.2f, %.2f, %.2f)", vec4f[0], vec4f[1], vec4f[2], vec4f[3]);
}

void	print_ambient_info(t_ambient ambient)
{
	printf("[ambient]\n");
	printf("ratio: %.2f\n", ambient.ratio);
	printf("hexcolor: %X\n", ambient.hexcolor);
}

void	print_sphere_info(t_sphere sphere)
{
	printf("[sphere]\n");
	printf("location: ");
	print_vec4f(sphere.location);
	printf("\ndiameter: %.2f", sphere.diameter);
	printf("\nhexcolor: %X\n", sphere.hexcolor);
}

void	print_plane_info(t_plane plane)
{
	printf("[plane]\n");
	printf("location: ");
	print_vec4f(plane.location);
	printf("\nvector: ");
	print_vec4f(plane.vector);
	printf("\nhexcolor: %X\n", plane.hexcolor);
}

void	print_cylinder_info(t_cylinder cylinder)
{
	printf("[cylinder]\n");
	printf("location: ");
	print_vec4f(cylinder.location);
	printf("\nvector: ");
	print_vec4f(cylinder.vector);
	printf("\ndiameter: %.2f", cylinder.diameter);
	printf("\nheight: %.2f", cylinder.height);
	printf("\nhexcolor: %X\n", cylinder.hexcolor);
}

void	print_camera_info(t_camera camera)
{
	printf("[camera]\n");
	printf("location: ");
	print_vec4f(camera.location);
	printf("\norientation: ");
	print_vec4f(camera.orientation);
	printf("\nFOV: %d\n", camera.fov);
}

void	print_light_info(t_light light)
{
	printf("[light]\n");
	printf("location: ");
	print_vec4f(light.location);
	printf("\nratio: %.2f", light.ratio);
	printf("\nhexcolor: %X\n", light.hexcolor);
}

void	print_scene_data(t_scene_data data)
{
	print_ambient_info(data.ambient);
	print_camera_info(data.camera);
	print_light_info(data.light);
	for (int i = 0; i < (int)data.obj_count[SPHERE]; i++)
		print_sphere_info(data.sphere[i]);
	for (int i = 0; i < (int)data.obj_count[PLANE]; i++)
		print_plane_info(data.plane[i]);
	for (int i = 0; i < (int)data.obj_count[CYLINDER]; i++)
		print_cylinder_info(data.cylinder[i]);
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
		close(fd);
		printf("Error: %s: not an .rt file.\n", argv[1]);
		return (1);
	}
	if (!parse_rt_file(&scene, fd))
	{
		close(fd);
		return (1);
	}
	print_scene_data(scene);
	if (scene.sphere)
		free(scene.sphere);
	if (scene.plane)
		free(scene.plane);
	if (scene.cylinder)
		free(scene.cylinder);
	close(fd);
	return (0);
}
