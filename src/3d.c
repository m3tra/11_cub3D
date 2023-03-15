/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:00:27 by fporto            #+#    #+#             */
/*   Updated: 2023/03/15 16:01:53 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Paints top half of the screen as ceiling_color and bottom half as floor_color
void	draw_3d_background(t_app *app)
{
	t_screen	*screen;
	u_int32_t	floor_color;
	u_int32_t	ceiling_color;
	size_t		x;
	size_t		y;

	screen = app->screen;
	floor_color = app->game->textures->floor_color;
	ceiling_color = app->game->textures->ceiling_color;
	y = 0;
	while (y < (screen->height / 2))
	{
		x = -1;
		while (++x < screen->width)
			my_mlx_pixel_put(screen->img, x, y, ceiling_color);
		++y;
	}
	while (y < screen->height)
	{
		x = -1;
		while (++x < screen->width)
			my_mlx_pixel_put(screen->img, x, y, floor_color);
		++y;
	}
}

int	draw3d(t_app *app)
{
	draw_3d_background(app);



	my_mlx_put_image_to_window(app);
	return (1);
}
