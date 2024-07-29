#include "parser.h"
#include "get_next_line.h"

t_vec4f	example_intersect_sphere(void *object, t_ray ray)
{
	t_sphere	*sphere = (t_sphere *)object;
	t_vec4f		ray_to_object = sphere->location - ray.origin;
	float		tc;
	float		d2;
	float		radius2;
	float		t1c;

	tc = dot_product_3d(ray_to_object, ray.direction);
	if (tc < 0.0f)
		return ((t_vec4f){0, 0, 0, -1});
	d2 = dot_product_3d(ray_to_object, ray_to_object) - (tc * tc);
	radius2 = sphere->radius * sphere->radius;
	if (d2 > radius2)
		return ((t_vec4f){0, 0, 0, -1});
	t1c = sqrtf(radius2 - d2);
	return (ray.origin + ray.direction * (tc - t1c));
}

t_vec4f	example_intersect_light(void *object, t_ray ray)
{
	t_light	*light = (t_light *)object;
	t_vec4f		ray_to_object = light->location - ray.origin;
	float		tc;
	float		d2;
	float		radius2;
	float		t1c;

	tc = dot_product_3d(ray_to_object, ray.direction);
	if (tc < 0.0f)
		return ((t_vec4f){0, 0, 0, -1});
	d2 = dot_product_3d(ray_to_object, ray_to_object) - (tc * tc);
	radius2 = light->radius * light->radius;
	if (d2 > radius2)
		return ((t_vec4f){0, 0, 0, -1});
	t1c = sqrtf(radius2 - d2);
	return (ray.origin + ray.direction * (tc - t1c));
}

t_vec4f	example_intersect_cylinder(void *object, t_ray ray)
{
	return ((t_vec4f){0, 0, 0, -1});
}

t_vec4f example_intersect_plane(void *object, t_ray ray)
{
	return ((t_vec4f){0, 0, 0, -1});
}

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

void print_light_data(void *object)
{
	t_light *light = (t_light *)object;
	printf("data light: x, y, z %f %f %f\n", light->location[0], light->location[1], light->location[2]);
}

void	assign_intersect_functions(t_object *current)
{
	const intersect_ptr	function_pointer[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		example_intersect_light,
		example_intersect_sphere,
		example_intersect_plane,
		example_intersect_cylinder,
	};
	const print_data	function_pointer_data[OBJ_TYPE_COUNT] = {
		NULL,
		print_camera_data,
		print_light_data,
		print_sphere_data,
		NULL,
		NULL,
	};
	const t_get_location	location_getters[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		t_get_location_light,
		t_get_location_sphere,
		NULL,
		NULL,
	};
	const t_get_color	color_getters[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		t_get_color_light,
		t_get_color_sphere,
		NULL,
		NULL,
	};
	const t_get_smoothness	get_smoothness[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		t_get_smoothness_sphere,
		NULL,
		NULL,
	};
	const t_get_brightness	get_brightness[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		t_get_brightness_light,
		NULL,
		NULL,
		NULL,
	};
	while (current)
	{
		current->intersect = (intersect_ptr)function_pointer[current->type];
		current->print_object_data = (print_data)function_pointer_data[current->type];
		current->get_location = (t_get_location)location_getters[current->type];
		current->get_color = (t_get_color)color_getters[current->type];
		current->get_smoothness = (t_get_smoothness)get_smoothness[current->type];
		current->get_brightness = (t_get_brightness)get_brightness[current->type];
		current = current->next;
	}
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
	// object_removetype(&scene->objects, LIGHT);
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
