#include "parser.h"
#include "get_next_line.h"

// int	intersect_sphere(void *object, t_ray ray)
// {
// 	t_sphere *sphere = (t_sphere *)object;

// 	const float squared = powf(obj_to_ray_vec[0], 2) + powf(obj_to_ray_vec[1], 2) + powf(obj_to_ray_vec[2], 2);
// 	// printf("hoi sphere:  %f, squared_root %f, color %d\n", sphere->radius, sqrtf(squared), sphere->color.color_code);
// 	if (squared <=  powf(sphere->radius, 2))
// 		return (TRUE);
// 	else
// 		return (FALSE);
// }

t_vec4f	intersect_sphere(void *object, t_ray ray)
{
	t_sphere	*sphere = (t_sphere *)object;
	t_vec4f		cam_to_obj = sphere->location - ray.origin;

	float dir_projected_len = dot_product_3d(cam_to_obj, ray.normalized_vec);

	if (dir_projected_len <= 0)
		return ((t_vec4f){0,0,0,-1});

	float tc = powf(dir_projected_len, 2);
	float d2 = dot_product_3d(cam_to_obj, cam_to_obj) - tc;

	if (d2 > powf(sphere->radius, 2))
		return ((t_vec4f){0,0,0,-1});
	float tc1 = sqrtf(powf(sphere->radius, 2) - d2);
	t_vec4f hitpoint = (t_vec4f)(ray.origin + (ray.normalized_vec * (tc - tc1)));
	hitpoint[3] = 1;
	return hitpoint;
}



// t_vec4f	intersect_cylinder(void *object, t_ray ray)
// {
// 	t_cylinder *cylinder = (t_cylinder *)object;


// 	// print_matrix_1_3(obj_to_ray_vec);
// 	float xy_plane_len = sqrtf(powf(obj_to_ray_vec[0], 2) + powf(obj_to_ray_vec[1], 2));
// 	float positive_z = obj_to_ray_vec[2];

// 	if (positive_z < 0)
// 		positive_z = positive_z * (float)-1;
// 	// printf("height %f\n0", cylinder->height);
// 	// printf("pos z %f\n",positive_z);

// 	if (xy_plane_len <= cylinder->diameter / 2 && positive_z <= cylinder->height)
// 		return (TRUE);
// 	else
// 		return (FALSE);
// }

// t_vec4f example_intersect_plane(void *object, t_ray ray)
// {
// 	return (FALSE);
// }

void print_sphere_data(void *object)
{
	t_sphere *sphere = (t_sphere *)object;
	printf("data object: x, y, z %f %f %f\n", sphere->location[0], sphere->location[1], sphere->location[2]);
}

void print_camera_data(void *object)
{
	t_camera *camera = (t_camera *)object;
	printf("data camera: x, y, z %f %f %f\n", camera->location[0], camera->location[1], camera->location[2]);
}

t_vec4f t_get_location_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return sphere->location;
}

t_vec4f t_get_location_cylinder(void *object)
{
	t_cylinder *cylinder = (t_cylinder *)object;

	return cylinder->location;
}

int t_get_color_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return sphere->color.color_code;
}

int t_get_color_cylinder(void *object)
{
	t_cylinder *cylinder = (t_cylinder *)object;

	return cylinder->color.color_code;
}

void	assign_intersect_functions(t_object *current)
{
	const intersect_ptr	function_pointer[OBJ_COUNT] = {
		NULL,
		NULL,
		NULL,
		intersect_sphere,
		NULL,
		NULL,
	};
	const print_data	function_pointer_data[OBJ_COUNT] = {
		NULL,
		print_camera_data,
		NULL,
		print_sphere_data,
		NULL,
		NULL,
	};
	const t_get_location	location_getters[OBJ_COUNT] = {
		NULL,
		NULL,
		NULL,
		t_get_location_sphere,
		NULL,
		t_get_location_cylinder,
	};
	const t_get_color	color_getters[OBJ_COUNT] = {
		NULL,
		NULL,
		NULL,
		t_get_color_sphere,
		NULL,
		t_get_color_cylinder,
	};
	while (current)
	{
		current->intersect = (intersect_ptr)function_pointer[current->type];
		current->print_object_data = (print_data)function_pointer_data[current->type];
		current->get_location = (t_get_location)location_getters[current->type];
		current->get_color = (t_get_color)color_getters[current->type];

		current = current->next;
	}
	// exit(0);
}

static void	objects_to_scene_data(t_scene_data *scene, t_object *current)
{
	while (current)
	{
		if (current->type == AMBIENT)
			scene->ambient = *(t_ambient *)current->object;
		else if (current->type == CAMERA)
			scene->camera = *(t_camera *)current->object;
		else if (current->type == LIGHT)
			scene->light = *(t_light *)current->object;
		current = current->next;
	}
	object_removetype(&scene->objects, AMBIENT);
	object_removetype(&scene->objects, CAMERA);
	object_removetype(&scene->objects, LIGHT);
	assign_intersect_functions(scene->objects);
}

static int	is_valid_object_count(int count, t_objectid type, int low, int high)
{
	if (count < low)
		fprintf(stderr, "Error: not enough ");
	else if (count > high)
		fprintf(stderr, "Error: too many ");
	else
		return (1);
	if (type == AMBIENT)
		fprintf(stderr, "ambient lighting elements. -> [%d-%d]\n", low, high);
	else if (type == CAMERA)
		fprintf(stderr, "cameras. -> [%d-%d]\n", low, high);
	else if (type == LIGHT)
		fprintf(stderr, "lights. -> [%d-%d]\n", low, high);
	else if (type == SPHERE)
		fprintf(stderr, "spheres. -> [%d-%d]\n", low, high);
	else if (type == PLANE)
		fprintf(stderr, "planes. -> [%d-%d]\n", low, high);
	else if (type == CYLINDER)
		fprintf(stderr, "cylinders. -> [%d-%d]\n", low, high);
	return (0);
}

static int	is_valid_scene(t_scene_data *scene)
{
	if (!is_valid_object_count(scene->obj_count[AMBIENT], AMBIENT, 1, 1) || \
		!is_valid_object_count(scene->obj_count[CAMERA], CAMERA, 1, 1) || \
		!is_valid_object_count(scene->obj_count[LIGHT], LIGHT, 1, 1) || \
		!is_valid_object_count(scene->obj_count[SPHERE], SPHERE, 0, 10) || \
		!is_valid_object_count(scene->obj_count[PLANE], PLANE, 0, 10) || \
		!is_valid_object_count(scene->obj_count[CYLINDER], CYLINDER, 0, 10))
		return (0);
	return (1);
}

/* calling get_next_line with -1 as fd frees buffer if its not empty */

int	parse_rt_file(t_scene_data *scene, int fd)
{
	char		*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (!parse_object(line, scene->obj_count, &scene->objects))
			{
				get_next_line(-1);
				return (clear_objects(scene->objects), free(line), 0);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!is_valid_scene(scene))
		return (clear_objects(scene->objects), 0);
	objects_to_scene_data(scene, scene->objects);
	return (1);
}
