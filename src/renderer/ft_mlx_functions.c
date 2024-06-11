/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:27:12 by rverhoev          #+#    #+#             */
/*   Updated: 2024/06/11 12:06:45 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minirt.h"
/**
 * mlxinit prepares essential data bts
*/
t_win	new_window(int w, int h, char *str)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
}

t_img	new_img(int w, int h, t_win window)
{
	t_img	image;

	image.win = window;
	image.img_ptr = mlx_new_image(window.mlx_ptr, w, h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

void	destroy_image(t_img img)
{
	if (img.img_ptr && img.win.mlx_ptr)
		mlx_destroy_image(img.win.mlx_ptr, img.img_ptr);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}