#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include "parser.h"
# define KEY_ESC 65307

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

static int	rgb_to_hex(unsigned char r, unsigned char g, unsigned char b)
{
	int hex;

	hex = r;
	hex = (hex << 8) | g;
	hex = (hex << 8) | b;
	return (hex);
}

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
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "minirt");
	img.img = mlx_new_image(data.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	data.img = &img;
	for (int i = 0; i < 1500; i++)
		put_pixel_to_img(&img, 10 + i, 10, rgb_to_hex(128, 30, 128));
	mlx_put_image_to_window(data.mlx, data.mlx_win, img.img, 0, 0);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, end_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, img.img);
	mlx_destroy_window(data.mlx, data.mlx_win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
