#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include "parser.h"
#include <math.h>
# define KEY_ESC 65307
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct
{
	void		*mlx;
	void		*mlx_win;
	t_img_data	*img;
}	t_mlx_data;

typedef struct
{
	t_vec4f	x;
	t_vec4f	y;
	t_vec4f	z;
	t_vec4f	w;
}	t_mat4f;

typedef struct
{
	t_vec4f	origin;
	t_vec4f	target;
}	t_ray;

static void	put_pixel_to_img(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * \
		(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	end_loop(void *mlx_ptr)
{
	mlx_loop_end(mlx_ptr);
	return (0);
}

static int	key_hook(int key, t_mlx_data *data)
{
	if (key == KEY_ESC)
		end_loop(data->mlx);
	return (0);
}

static void	add_background_fill(t_img_data *img)
{
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			double r = (double)x / WINDOW_WIDTH;
			double g = (double)y / WINDOW_HEIGHT;
			double b = 0.1;

			int ir = (int)(255.999 * r);
			int ig = (int)(255.999 * g);
			int ib = (int)(255.999 * b);
			put_pixel_to_img(img, x, y, clamped_rgb_to_hex(ir, ig, ib));
			// put_pixel_to_img(img, x, y, 0x000000FF);
		}
	}
}

int	intersects_sphere(t_sphere sphere, int x, int y)
{
	if ()
	return (1);
}

// float	vec_distance(t_vec4f origin, t_vec4f target)
// {

// }

int	intersects_surface(t_scene_data *scene, int x, int y)
{
	// t_vec4f	closest_intersect;
	// t_vec4f	intersect;
	int	current_count;

	current_count = scene->obj_count[SPHERE];
	if (current_count)
	{
		current_count--;
		if (intersects_sphere(scene->sphere[current_count], x, y))
			return (1);
	}
	return (0);
}

static void	fire_rays(t_scene_data *scene, t_img_data *img)
{
	const double	ray_x_step = WINDOW_WIDTH / (tan(scene->camera.fov) * \
								((double)WINDOW_WIDTH / (double)WINDOW_HEIGHT));
	const double	ray_y_step = WINDOW_HEIGHT / tan(scene->camera.fov);
	int	x = 0;
	int	y = 0;

	while (y < WINDOW_HEIGHT)
	{
		while (x < WINDOW_WIDTH)
		{
			if (intersects_with_shape(scene, x * ray_x_step + ray_x_step, \
										y * ray_y_step + ray_y_step))
				put_pixel_to_img(img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	render_scene(t_scene_data *scene)
{
	t_img_data	img;
	t_mlx_data	data;

	(void)scene;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "minirt");
	img.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	data.img = &img;
	add_background_fill(data.img);
	fire_rays(scene, data.img);
	mlx_put_image_to_window(data.mlx, data.mlx_win, img.img, 0, 0);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, end_loop, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_hook, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, img.img);
	mlx_destroy_window(data.mlx, data.mlx_win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
