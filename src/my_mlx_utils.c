/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:13:00 by fporto            #+#    #+#             */
/*   Updated: 2023/06/14 20:21:57 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, u_int32_t color)
{
	char	*dst;

	if (!img)
		err_exit("NULL img @my_mlx_pixel_put", NULL);
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(u_int32_t *)dst = color;
}

void	my_mlx_pixel_put2(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	dst[3] = color >> 24;
	dst[2] = color >> 16;
	dst[1] = color >> 8;
	dst[0] = color;
}

char	*my_mlx_get_data_addr(t_img *img)
{
	char	*addr;

	if (!img)
		err_exit("NULL img @my_mlx_get_data_addr", NULL);
	addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (!addr)
		err_exit("Failed mlx_get_data_addr @my_mlx_get_data_addr", NULL);
	return (addr);
}

t_img	*my_mlx_new_image(void *mlx, int width, int height)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		err_exit("Failed ft_calloc @my_mlx_new_image", NULL);
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		err_exit("Failed mlx_new_image @my_mlx_new_image", NULL);
	img->addr = my_mlx_get_data_addr(img);
	return (img);
}

void	my_mlx_put_image_to_window(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->screen->win, app->screen->img->img, \
		0, 0);
}
