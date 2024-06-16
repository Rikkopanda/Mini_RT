// #pragma once

#ifndef MINIRT_H
# define MINIRT_H

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include "../../lib/minilibx-linux/mlx.h"
# include <stdlib.h>
# include "libft.h"
# define PRINT_DEBUG 1
# include "color.h"


# include "objects.h"

typedef struct s_ray	t_ray;

# define WINDOW_HEIGHT 700
# define WINDOW_WIDTH 300

typedef struct s_scene_data t_scene_data;

# define DEGR_10_IN_RAD 0.1745329252
# define M_PI           3.14159265358979323846

enum e_error_codes
{
	IN_BOUNDS,
	OUT_OF_BOUNDS
};

enum bool
{
	FALSE,
	TRUE
};

enum keys
{
	ON_ESC = 65307
};

enum e_hex_code
{
	NADA = -1,
	BLACK = 0x000000,
	GREY = 0x808080,
	WHITE = 0xFFFFFF,
	RED = 0xFF00FF,
	GREEN = 0x00FFFF,
	BLUE = 0x000FFF,
	ORANGE = 0xFFA500
};

enum e_key_codes
{
	UP = 65362,
	DOWN = 65364,
	LEFT = 65361,
	RIGHT = 65363
};

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}		t_win;

typedef struct s_img
{
	t_win	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}		t_img;

typedef struct s_ambient_lightning //what does this mean, just reflected light?
{
	int		rgb[3]; // https://www.reddit.com/r/spaceengineers/comments/3e0k38/rgb_values_for_various_types_of_realworld_lights/
	float	lightning_ratio; // range 0.0-1.0
} t_ambient_lightning;

typedef struct s_light_source
{
	t_vec4f	position;
	int		rgb[3];
	float	brightness; // range 0.0-1.0
} t_light_source;

typedef struct s_transform_index
{
	int	j;
	int	i;
	int	l;
	int	m;
}	t_transform_index;

typedef struct s_ray_sending_tools
{
	int 	pixel_x;
	int 	pixel_y;
	float 	start_angle_horiz;
	float 	start_angle_vert;
	float 	angle_horiz;
	float 	angle_vert;
	int		half_screen_width;
	int		half_screen_height;
	float	perpendicular_distance_horiz_triangle;
	float	perpendicular_distance_vert_triangle;
} t_ray_sending_tools;

typedef struct s_scene_data
{
	int			obj_count[OBJ_COUNT];
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_ray		ray;
	t_object	*objects;
	t_win		mlx;
	t_img		image;
}	t_scene_data;


void	matrix_multiplication(t_vec4f comp[3], t_ray *ray, t_vec4f camera_vector);
void	matrix_multiply_1x3_3x3(t_vec4f *m1, t_vec4f m2[3], t_vec4f *result_m);
void	compilation_matrix(t_vec4f comp[3], t_vec4f R[3], t_vec4f R3[3]);
void	copy_matrix(t_vec4f *dst, t_vec4f src);
void	init_comp_m(t_vec4f comp[3]);

void	normalize_vector(t_vec4f *v);
void	vector_scaling(t_vec4f *v, float scale);
t_vec4f t_vec4f_construct(float x, float y, float z);


int		interpolate(int color_A, int color_B, float t);
void	init_ray_send_tools(t_ray_sending_tools *r_t, t_scene_data *scene);

void	init_t_around_z(t_vec4f R[3], float rad);
void	init_t_around_y(t_vec4f R[3], float rad);
void	init_t_around_x(t_vec4f R[3], float rad);
void	init_result(t_vec4f *M);
float	ft_degr_to_rad(float x);
float	ft_rad_to_degr(float x);
int		render_scene(t_scene_data *data);
void	send_rays(t_scene_data *scene);
int		hit_ray(t_scene_data *scene, t_vec4f new_dir_method_ray_test);

void	put_pixel_img(t_img img, int x, int y, int color);
void	init_rgb(t_color *rgb, int color);
void 	init_rgb_f(t_vec4f *rgb_f, int rgb[3]);
void	make_rgb_with_normalized_rgb_f(int rgb[3], t_vec4f rgb_f);
int		create_color(int r, int g, int b);

void	print_matrix_3_3(t_vec4f m[3]);
void	print_matrix_1_3(t_vec4f m);

int		handle_input(int keysym, t_scene_data *data);

t_win	new_window(int w, int h, char *str);
t_img	new_img(int w, int h, t_win window);
void	destroy_image(t_img img);

#endif