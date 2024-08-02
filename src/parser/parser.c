#include "parser.h"
#include "get_next_line.h"

void	swapf(float *a, float *b)
{
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

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
	float		t1;
	float		t2;

	tp = dot_product_3d(ray_to_object, ray.direction);
	if (tp < 0.0f)
		return ((t_vec4f){0, 0, 0, -1});
	tc_squared = dot_product_3d(ray_to_object, ray_to_object) - (tp * tp);
	radius_squared = sphere->radius * sphere->radius;
	if (tc_squared > radius_squared)
		return ((t_vec4f){0, 0, 0, -1});
	ti = sqrtf(radius_squared - tc_squared);
	t1 = tp - ti;
	t2 = tp + ti;
	printf("t1 %.4f, t2 %.4f\n", t1, t2);
	if (t2 < t1)
		return (ray.origin + ray.direction * t2);
	return (ray.origin + ray.direction * t1);
}

typedef struct s_ray_to_cylinder
{
	t_vec4f	slice_center;
	t_vec4f	top_center;
	t_vec4f	bottom_center;
	float	cap_center_distance;
}	t_ray_to_cylinder;

t_vec4f	intersect_cylinder(void *object, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder *)object;
	t_ray_to_cylinder	intersect;
	t_vec4f				X;
	float				a;
	float				b;
	float				c;
	float				d_dot_v;
	float				x_dot_v;
	float				t1;
	float				t2;
	float				tempt;
	float				discriminant;
	t_vec4f				intersect1;
	t_vec4f				intersect2;
	float				height1;
	float				height2;
	float				top_cap;
	float				bottom_cap;

	intersect.top_center = cylinder->location + cylinder->vector * (cylinder->height / 2);
	intersect.bottom_center = cylinder->location - cylinder->vector * (cylinder->height / 2);
	X = ray.origin - cylinder->location;
	d_dot_v = dot_product_3d(ray.direction, cylinder->vector);
	x_dot_v = dot_product_3d(X, cylinder->vector);
	a = dot_product_3d(ray.direction, ray.direction) - d_dot_v * d_dot_v;
	b = 2 * (dot_product_3d(ray.direction, X) - d_dot_v * x_dot_v);
	c = dot_product_3d(X, X) - x_dot_v * x_dot_v - cylinder->radius * cylinder->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ((t_vec4f){0, 0, 0, -1});
	t1 = (-b - sqrtf(discriminant)) / (2 * a);
	t2 = (-b + sqrtf(discriminant)) / (2 * a);
	if (t1 > t2)
	{
		tempt = t1;
		t1 = t2;
		t2 = tempt;
	}
	intersect1 = ray.origin + ray.direction * t1;
	intersect2 = ray.origin + ray.direction * t2;
	height1 = dot_product_3d(intersect1 - cylinder->location, cylinder->vector);
	height2 = dot_product_3d(intersect2 - cylinder->location, cylinder->vector);
	if (height1 >= -cylinder->height / 2 && height1 <= cylinder->height / 2)
		return (intersect1);
	if (height2 >= -cylinder->height / 2 && height2 <= cylinder->height / 2)
		return (intersect2);
	top_cap = dot_product_3d(cylinder->location - ray.origin, cylinder->vector) / d_dot_v;
	if (top_cap > 0)
	{
		t_vec4f	top_intersect = ray.origin + ray.direction * top_cap;
		if (dot_product_3d(top_intersect - intersect.top_center, top_intersect - intersect.top_center) <= cylinder->radius * cylinder->radius)
			return (top_intersect);
	}
	bottom_cap = dot_product_3d((cylinder->location - cylinder->vector * cylinder->height) - ray.origin, cylinder->vector) / d_dot_v;
	if (bottom_cap > 0)
	{
		t_vec4f	bottom_intersect = ray.origin + ray.direction * bottom_cap;
		if (dot_product_3d(bottom_intersect - intersect.bottom_center, bottom_intersect - intersect.bottom_center) <= cylinder->radius * cylinder->radius)
			return (bottom_intersect);
	}

	return ((t_vec4f){0, 0, 0, -1});
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
