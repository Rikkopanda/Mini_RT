
#include "parser.h"
#include "libft.h"
#include "minirt.h"

int	get_r(int color)
{
	return (color >> 16 & 0xFF);
}

int	get_g(int color)
{
	return (color >> 8 & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}

void init_rgb(t_color *color, int color_code)
{
	color->rgb[0] = get_r(color_code);
	color->rgb[1] = get_g(color_code);
	color->rgb[2] = get_b(color_code);
}

void init_rgb_f(t_vec4f rgb_f, int rgb[3])
{
	rgb_f[0] = rgb[0];
	rgb_f[1] = rgb[1];
	rgb_f[2] = rgb[2];
}
void make_rgb_with_normalized_rgb_f(int rgb[3], t_vec4f rgb_f)
{
	rgb[0] = (rgb_f[0] * (float)255);
	rgb[1] = (rgb_f[1] * (float)255);
	rgb[2] = (rgb_f[2] * (float)255);
}

int create_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	interpolate(int color_A, int color_B, float t)
{
	t_color rgb_a;
	t_color rgb_b;
	t_color rgb_interpolate;

	init_rgb(&rgb_a, color_A);
	init_rgb(&rgb_b, color_B);
	rgb_interpolate.rgb[0] = rgb_a.rgb[0] + (rgb_b.rgb[0] - rgb_a.rgb[0]) * t;
	rgb_interpolate.rgb[1] = rgb_a.rgb[1] + (rgb_b.rgb[1] - rgb_a.rgb[1]) * t;
	rgb_interpolate.rgb[2] = rgb_a.rgb[2] + (rgb_b.rgb[2] - rgb_a.rgb[2]) * t;
	return (create_color(rgb_interpolate.rgb[0], rgb_interpolate.rgb[1], rgb_interpolate.rgb[2]));
}
