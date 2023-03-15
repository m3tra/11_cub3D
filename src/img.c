/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:06 by fporto            #+#    #+#             */
/*   Updated: 2023/03/13 20:59:00 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	frame(t_app *app)
// {
// 	static int	frame = 1;

// 	if (app->screen->frame_count % 37 == 0)
// 	{
// 		++frame;
// 		++app->screen->frame_count;
// 	}
// 	if (frame == 5)
// 		frame = 1;
// 	return (frame);
// }

t_img	*import_image(t_app *app, char tile, int x, int y)
{
	(void)tile;
	(void)x;
	(void)y;

	t_img	*img;

	// img = ft_calloc(1, sizeof(*img));
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		err_exit("Failed ft_calloc @import_image", app);

	// if (tile == EMPTY)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_EMPTY, &x, &y);
	// else if (tile == WALL)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_WALL, &x, &y);
	// else if (tile == AMMO)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_COLL0, &x, &y);
	// else if (tile == AMMO)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_COLL1, &x, &y);
	// else if (tile == AMMO)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_COLL2, &x, &y);
	// else if (tile == AMMO)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_COLL3, &x, &y);
	// else if (tile == EXIT)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_EXIT, &x, &y);
	// else if (tile == PLAYER)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_PLAYER, &x, &y);
	// else if (tile == ENEMY)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_ENEMY0, &x, &y);
	// else if (tile == ENEMY)
	// 	img->img = mlx_xpm_file_to_image(app->mlx, TEX_ENEMY1, &x, &y);

	if (!img->img)
		err_exit("Missing texture", app);

	return (img);
}

// Draws respective tile's sprite on screen->img taking into account transparency
void	place_img(t_app *app, char tile, t_int_p p)
{
	t_img	*img;
	size_t	y;
	size_t	x;
	int		pixel;

	img = import_image(app, tile, TILE_SIZE, TILE_SIZE);

	// img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, \
	// 	&img->endian);
	img->addr = my_mlx_get_data_addr(img);

	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE) {
			pixel = *(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8)));
			if ((pixel & 0xff000000) != 0xff000000)
				my_mlx_pixel_put(app->screen->img, p.x * TILE_SIZE + x,
					p.y * TILE_SIZE + y, pixel);
		}
	}
	mlx_destroy_image(app->mlx, img->img);
	ft_free(img);
}
