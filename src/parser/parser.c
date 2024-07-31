#include "parser.h"
#include "get_next_line.h"
/**
 * @note 
 * source: https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
 * source: https://nachodevblog.com/posts/ray-cylinder-intersection/
 */
t_vec4f	intersect_sphere(void *object, t_ray ray)
{
	t_sphere	*sphere = (t_sphere *)object;
	t_vec4f		ray_to_object = sphere->location - ray.origin;
	float		tp;
	float		tc_squared;
	float		radius_squared;
	float		ti;

	tp = dot_product_3d(ray_to_object, ray.direction);
	if (tp < 0.0f)
		return ((t_vec4f){0, 0, 0, -1});
	tc_squared = dot_product_3d(ray_to_object, ray_to_object) - (tp * tp);
	radius_squared = sphere->radius * sphere->radius;
	if (tc_squared > radius_squared)
		return ((t_vec4f){0, 0, 0, -1});
	ti = sqrtf(radius_squared - tc_squared);
	return (ray.origin + ray.direction * (tp - ti));
}

t_vec4f	intersect_cylinder(void *object, t_ray ray)
{
	t_cylinder	*cylinder = (t_cylinder *)object;
	t_vec4f		slice_center = cylinder->location;
	t_vec4f		ray_to_slice_center;
	t_vec4f		ray_slice_direction = ray.direction;
	float		tp;
	float		tc_squared;
	float		radius_squared;
	float		ti;
	float		ip;
	float		cosb;
	float		pp;
	t_vec4f		point;
	t_vec4f		y_direction;
	float		cosw;
	float		D;
	float		A;

	slice_center[1] = ray.origin[1];
	ray_to_slice_center = slice_center - ray.origin;
	ray_slice_direction[1] = 0;
	normalize_vector(&ray_slice_direction);
	tp = dot_product_3d(ray_slice_direction, ray_to_slice_center);
	if (tp < 0.0f)
		return ((t_vec4f){0, 0, 0, -1});
	tc_squared = dot_product_3d(ray_to_slice_center, ray_to_slice_center) - (tp * tp);
	radius_squared = cylinder->radius * cylinder->radius;
	if (tc_squared > radius_squared)
		return ((t_vec4f){0, 0, 0, -1});
	ti = sqrtf(radius_squared - tc_squared);
	ip = tp - ti;
	normalize_vector(&ray_to_slice_center);
	cosb = dot_product_3d(ray.direction, ray_to_slice_center);
	if (cosb == 0.0f)
		return (ray.origin + ray_slice_direction * ip);
	pp = ip / cosb;
	point = ray.origin + ray.direction * pp;
	if (fabsf(point[1] - cylinder->location[1]) <= cylinder->height / 2)
		return (point);
	if (ray.direction[1] <= 0)
		y_direction = (t_vec4f){0, -1, 0, 1};
	else
		y_direction = (t_vec4f){0, 1, 0, 1};
	A = ray.origin[1] - cylinder->height / 2;
	cosw = dot_product_3d(ray.direction, y_direction);
	if (cosw == 0.0f)
		return ((t_vec4f){0, 0, 0, -1});
	D =  cylinder->height / cosw;
	point = ray.origin + ray.direction * D;
	if (sqrtf(point[0] * point[0] + point[2] * point[2]) > cylinder->radius)
		return ((t_vec4f){0, 0, 0, -1});
	return (point);
}

t_vec4f intersect_plane(void *object, t_ray ray)
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

t_vec4f get_location_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return (sphere->location);
}

t_vec4f	get_color_sphere(void *object)
{
	t_sphere *sphere = (t_sphere *)object;

	return (sphere->color.rgb_f);
}

t_vec4f get_location_cylinder(void *object)
{
	t_cylinder *cylinder = (t_cylinder *)object;

	return (cylinder->location);
}

t_vec4f	get_color_cylinder(void *object)
{
	t_cylinder *cylinder = (t_cylinder *)object;

	return (cylinder->color.rgb_f);
}

t_vec4f	get_normal_sphere(void *object, t_vec4f point)
{
	t_sphere *sphere = (t_sphere *)object;

	return (point - sphere->location);
}

t_vec4f	get_normal_cylinder(void *object, t_vec4f point)
{
	t_cylinder *cylinder = (t_cylinder *)object;
	t_vec4f		normal;
	
	normal = point - cylinder->location;
	normal[1] = 0;
	return (normal);
}

void	assign_intersect_functions(t_object *current)
{
	const intersect_ptr	function_pointer[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		intersect_sphere,
		intersect_plane,
		intersect_cylinder,
	};
	const print_data	function_pointer_data[OBJ_TYPE_COUNT] = {
		NULL,
		print_camera_data,
		NULL,
		print_sphere_data,
		NULL,
		NULL,
	};
	const t_get_location	location_getters[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		get_location_sphere,
		NULL,
		get_location_cylinder,
	};
	const t_get_color	color_getters[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		get_color_sphere,
		NULL,
		get_color_cylinder,
	};
	const t_get_normal	normal_getters[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		get_normal_sphere,
		NULL,
		get_normal_cylinder,
	};
	while (current)
	{
		current->intersect = (intersect_ptr)function_pointer[current->type];
		current->print_object_data = (print_data)function_pointer_data[current->type];
		current->get_location = (t_get_location)location_getters[current->type];
		current->get_color = (t_get_color)color_getters[current->type];
		current->get_normal = (t_get_normal)normal_getters[current->type];
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
