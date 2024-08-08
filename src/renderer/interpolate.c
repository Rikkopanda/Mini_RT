
#include "minirt.h"

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

float	interpolatef(float A, float B, float t)
{
	float result;

	result = A + (B - A) * t; // 0.5 + (1 - 0.5) * 1 = 1
	return result;
}

/**
 * make factor fall between 0 and 1
*/
void	fit_interpolation_range(float *rgb_factor)
{
	*rgb_factor += 1;
	*rgb_factor *= 0.5;
}
