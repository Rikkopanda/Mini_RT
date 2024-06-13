#include <stdio.h>
#include "parser.h"

void	print_vec4f(t_vec4f vec4f)
{
	printf("(%.2f, %.2f, %.2f, %.2f)", vec4f[0], vec4f[1], vec4f[2], vec4f[3]);
}

void	print_ambient_info(t_ambient ambient)
{
	printf("[ambient]\n");
	printf("ratio: %.2f\n", ambient.ratio);
	printf("hexcolor: #%06X\n", ambient.color.color_code);
}

void	print_sphere_info(t_sphere sphere)
{
	printf("[sphere]\n");
	printf("location: ");
	print_vec4f(sphere.location);
	printf("\ndiameter: %.2f", sphere.diameter);
	printf("\nhexcolor: #%06X\n", sphere.color.color_code);
}

void	print_plane_info(t_plane plane)
{
	printf("[plane]\n");
	printf("location: ");
	print_vec4f(plane.location);
	printf("\nvector: ");
	print_vec4f(plane.vector);
	printf("\nhexcolor: #%06X\n", plane.color.color_code);
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
	printf("\nhexcolor: #%06X\n", cylinder.color.color_code);
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
	printf("\nhexcolor: #%06X\n", light.color.color_code);
}

void	print_scene_data(t_scene_data data)
{
	print_ambient_info(data.ambient);
	print_camera_info(data.camera);
	print_light_info(data.light);
	while (data.objects)
	{
		if (data.objects->type == SPHERE)
			print_sphere_info(*(t_sphere *)data.objects->object);
		else if (data.objects->type == PLANE)
			print_plane_info(*(t_plane *)data.objects->object);
		else if (data.objects->type == CYLINDER)
			print_cylinder_info(*(t_cylinder *)data.objects->object);
		data.objects = data.objects->next;
	}
}
