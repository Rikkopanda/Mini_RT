#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include "parser.h"
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
	t_vec4f	origin;
	t_vec4f	direction;
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
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			// double r = (double)x / WINDOW_WIDTH;
			// double g = (double)y / WINDOW_HEIGHT;
			// double b = 0.8;

			// int ir = (int)(255.999 * r);
			// int ig = (int)(255.999 * g);
			// int ib = (int)(255.999 * b);
			// put_pixel_to_img(data.img, x, y, clamped_rgb_to_hex(ir, ig, ib));
			put_pixel_to_img(data.img, x, y, 0x000000FF);
		}
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, img.img, 0, 0);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, end_loop, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_hook, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, img.img);
	mlx_destroy_window(data.mlx, data.mlx_win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
