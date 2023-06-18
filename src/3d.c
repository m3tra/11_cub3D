/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:00:27 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 08:42:54 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d_background(t_app *app, u_int32_t f_clr, u_int32_t c_clr)
{
	t_screen	*screen;
	int			x;
	int			y;

	screen = app->screen;
	y = 0;
	while (y < (screen->height / 2))
	{
		x = -1;
		while (++x < screen->width)
			my_mlx_pixel_put(screen->img, x, y, c_clr);
		++y;
	}
	while (y < screen->height)
	{
		x = -1;
		while (++x < screen->width)
			my_mlx_pixel_put(screen->img, x, y, f_clr);
		++y;
	}
}

void	draw_walls(t_app *app, t_float_p pos, float pa)
{
	t_check	*check;
	double	ang;
	int		a;
	int		b;
	int		c;

	a = -1;
	while (++a < WIN_WIDTH)
	{
		ang = (a * FOV / WIN_WIDTH) - FOV / 2;
		ang = fmod(pa + ang + (2 * M_PI), (2 * M_PI));
		check = check_wall(app->game, pos, ang, pa);
		b = check->lo -1;
		while (++b < WIN_HEIGHT && b < check->lh + check->lo)
		{
			c = -1;
			while (++c < 1)
				my_mlx_pixel_put2(app->screen->img, a + c, b,
					check->texture[(int)check->tex.y][(int)(check->tex.x)]);
			check->tex.y += TEXTURE_SIZE / (double)check->lh;
			if (check->tex.y >= TEXTURE_SIZE)
				check->tex.y = TEXTURE_SIZE - 1;
		}
		free(check);
	}
}

float	fix_angle(float pa)
{
	if (pa < M_PI)
		pa = (M_PI / 2) - (pa - (M_PI / 2));
	else if (pa < (3 * M_PI / 2))
		pa = 2 * M_PI - (pa - M_PI);
	else
		pa = M_PI + (2 * M_PI - pa);
	return (pa);
}

int	draw3d(t_app *app)
{
	float		pa;

	pa = fix_angle(app->game->player.facing);
	draw_3d_background(app, app->game->textures->floor_color,
		app->game->textures->ceiling_color);
	draw_walls(app, app->game->player.pos, pa);
	draw2d(app);
	my_mlx_put_image_to_window(app);
	return (1);
}
