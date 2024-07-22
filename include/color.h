#ifndef COLOR_H
# define COLOR_H

typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));

typedef t_vec4f t_vec4f_color;
typedef struct s_color
{
	int		rgb[3];
	int		color_code;
	t_vec4f	rgb_f;
} t_color;

#endif