/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:30:46 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 08:32:49 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	pick_color(char map_tile)
{
	u_int32_t	color;

	if (map_tile == WALL)
		color = create_trgb(255, 0, 0, 0);
	else if (map_tile == DOOR)
		color = create_trgb(255, 255, 0, 255);
	else if (map_tile == TORCH)
		color = create_trgb(255, 255, 255, 0);
	else
		color = create_trgb(255, 255, 255, 255);
	return (color);
}

void	draw_player(int x, int y, t_screen *s)
{
	draw_circle2(s->img, s->width - x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE
		/ 2, y * MINIMAP_TILE_SIZE
		+ MINIMAP_TILE_SIZE / 2, create_trgb(255, 0, 0, 255));
}

void	draw_square(int x, int y, int color, t_screen *s)
{
	int	k;
	int	l;

	k = -1;
	while (++k < MINIMAP_TILE_SIZE)
	{
		l = -1;
		while (++l < MINIMAP_TILE_SIZE)
		{
			if (s->width - x * MINIMAP_TILE_SIZE + k >= 0
				&& s->width - x * MINIMAP_TILE_SIZE + k < s->width
				&& y * MINIMAP_TILE_SIZE + l >= 0
				&& y * MINIMAP_TILE_SIZE + l < (int)s->height)
				my_mlx_pixel_put(s->img, s->width - x * MINIMAP_TILE_SIZE + k,
					y * MINIMAP_TILE_SIZE + l, color);
		}
	}
}

void	render_map(t_game *game, t_screen *s)
{
	int			j;
	int			i;
	u_int32_t	c;

	i = -1;
	while (++i < (int)game->map->max_height)
	{
		j = 0;
		while (++j <= (int)game->map->max_width)
		{
			c = pick_color(game->map->map_arr[i][game->map->max_width - j]);
			draw_square(j, i, c, s);
		}
	}
	draw_player((game->map->max_width - (int)game->player.pos.x),
		(int)game->player.pos.y, s);
}

void	draw2d(t_app *app)
{
	render_map(app->game, app->screen);
}
