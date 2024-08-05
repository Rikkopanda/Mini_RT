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

typedef struct s_cylinder_intersect
{
	t_vec4f	top_center;
	t_vec4f	bottom_center;
	float	a;
	float	b;
	float	d_dot_v;
	float	t1;
	float	t2;
	float	t_top;
	float	t_bottom;
	float	t_min;
}	t_cylinder_intersect;

/**
 * @note
 * discriminant = b² * 4ac;
 */
float	calculate_discriminant(t_ray ray, const t_cylinder *cylinder, \
								t_cylinder_intersect *intersect)
{
	const t_vec4f	x = ray.origin - cylinder->location;
	const float		d_dot_v = dot_product_3d(ray.direction, cylinder->vector);
	const float		x_dot_v = dot_product_3d(x, cylinder->vector);
	float			c;

	intersect->a = dot_product_3d(ray.direction, ray.direction) - d_dot_v * d_dot_v;
	intersect->b = 2 * (dot_product_3d(ray.direction, x) - d_dot_v * x_dot_v);
	c = dot_product_3d(x, x) - x_dot_v * x_dot_v - cylinder->radius * cylinder->radius;
	intersect->d_dot_v = d_dot_v;
	return (intersect->b * intersect->b - 4 * intersect->a * c);
}

void	validate_intersection_distance(t_ray ray, const t_cylinder *cylinder,
										t_cylinder_intersect *intersect)
{
	float			height1;
	float			height2;
	const t_vec4f	point[4] = {
		ray.origin + ray.direction * intersect->t1,
		ray.origin + ray.direction * intersect->t2,
		ray.origin + ray.direction * intersect->t_top,
		ray.origin + ray.direction * intersect->t_bottom,
	};

	height1 = dot_product_3d(point[0] - cylinder->location, cylinder->vector) \
				/ vector_length(cylinder->vector);
	height2 = dot_product_3d(point[1] - cylinder->location, cylinder->vector) \
				/ vector_length(cylinder->vector);
	if (height1 < -cylinder->height / 2 || height1 > cylinder->height / 2)
		intersect->t1 = -1;
	if (height2 < -cylinder->height / 2 || height2 > cylinder->height / 2)
		intersect->t2 = -1;
	if (vector_length(point[2] - cylinder->location - cylinder->vector * \
		(cylinder->height / 2)) > cylinder->radius || intersect->t_top < 0)
		intersect->t_top = -1;
	if (vector_length(point[3] - cylinder->location + cylinder->vector * \
		(cylinder->height / 2)) > cylinder->radius || intersect->t_bottom < 0)
		intersect->t_bottom = -1;
}

float	closest_intersect_distance(float t1, float t2, \
									float t_top, float t_bottom)
{
	float	t_min;

	t_min = INFINITY;
	if (t1 > 0)
		t_min = fminf(t_min, t1);
	if (t2 > 0)
		t_min = fminf(t_min, t2);
	if (t_top > 0)
		t_min = fminf(t_min, t_top);
	if (t_bottom > 0)
		t_min = fminf(t_min, t_bottom);
	if (t_min < INFINITY)
		return (t_min);
	return (-1);
}									

/**
 * @note
 * Source: https://stackoverflow.com/questions/73866852/ray-cylinder-intersection-formula
 * Source: https://en.wikipedia.org/wiki/Quadratic_formula
 */
t_vec4f	intersect_cylinder(void *object, t_ray ray)
{
	const t_cylinder		*cylinder = (t_cylinder *)object;
	t_cylinder_intersect	intersect;
	float					discriminant;

	intersect.top_center = cylinder->location + cylinder->vector * (cylinder->height / 2);
	intersect.bottom_center = cylinder->location - cylinder->vector * (cylinder->height / 2);
	discriminant = calculate_discriminant(ray, cylinder, &intersect);
	if (discriminant < 0)
		return ((t_vec4f){0, 0, 0, -1});
	intersect.t1 = (-intersect.b - sqrtf(discriminant)) / (2 * intersect.a);
	intersect.t2 = (-intersect.b + sqrtf(discriminant)) / (2 * intersect.a);
	if (intersect.t1 > intersect.t2)
		swapf(&intersect.t1, &intersect.t2);
	intersect.t_top = dot_product_3d(intersect.top_center - ray.origin, cylinder->vector) / intersect.d_dot_v;
	intersect.t_bottom = dot_product_3d(intersect.bottom_center - ray.origin, cylinder->vector) / intersect.d_dot_v;
	validate_intersection_distance(ray, cylinder, &intersect);
	intersect.t_min = closest_intersect_distance(intersect.t1, intersect.t2, intersect.t_top, intersect.t_bottom);
	if (intersect.t_min == -1)
		return ((t_vec4f){0, 0, 0, -1});
	return (ray.origin + ray.direction * intersect.t_min);
}

t_vec4f intersect_plane(void *object, t_ray ray)
{
	const t_plane	*plane = (t_plane *)object;
	float			t;
	float			denominator;

	denominator = dot_product_3d(plane->vector, ray.direction);
	if (fabsf(denominator) <= 1e-4f)
		return ((t_vec4f){0, 0, 0, -1});
	t = -(dot_product_3d(plane->vector, ray.origin) + dot_product_3d(plane->location, -plane->vector)) / denominator;
	if (t <= 1e-4f)
		return ((t_vec4f){0, 0, 0, -1});
	return (ray.origin + ray.direction * t);
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

t_vec4f get_location_plane(void *object)
{
	t_plane *plane = (t_plane *)object;

	return (plane->location);
}

t_vec4f get_color_plane(void *object)
{
	t_plane *plane = (t_plane *)object;

	return (plane->color.rgb_f);
}

t_vec4f get_normal_plane(void *object, t_vec4f point)
{
	t_plane *plane = (t_plane *)object;

	return (plane->vector);
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
	t_cylinder 		*cylinder = (t_cylinder *)object;
	const t_vec4f	top_center = cylinder->location + \
							cylinder->vector * (cylinder->height / 2);
	const t_vec4f	bottom_center = cylinder->location - \
							cylinder->vector * (cylinder->height / 2);
	t_vec4f			perpendicular_point;
	const float		error = 0.001f;
	
	if (fabsf(dot_product_3d(point - top_center, cylinder->vector)) < error)
		return (cylinder->vector);
	if (fabsf(dot_product_3d(point - bottom_center, cylinder->vector)) < error)
		return (-cylinder->vector);
	perpendicular_point = cylinder->location + cylinder->vector * \
				dot_product_3d(point - cylinder->location, cylinder->vector);
	point -= perpendicular_point;
	return (normalize_vector(&point));
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
		get_location_plane,
		get_location_cylinder,
	};
	const t_get_color	color_getters[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		get_color_sphere,
		get_color_plane,
		get_color_cylinder,
	};
	const t_get_normal	normal_getters[OBJ_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		get_normal_sphere,
		get_normal_plane,
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
