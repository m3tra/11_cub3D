/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:30:46 by fporto            #+#    #+#             */
/*   Updated: 2023/06/16 17:30:11 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define M_P2	(M_PI/2)
#define M_P3	(3*M_PI/2)
#define DR		0.01745329

// Paints entire screen as gray
void	draw_2d_background(t_app *app)
{
	t_screen	*screen;
	size_t		x;
	size_t		y;

	screen = app->screen;
	y = -1;
	while (++y < screen->height / 6)
	{
		x = -1;
		while (++x < screen->width / 6)
			my_mlx_pixel_put(screen->img, x, y, create_trgb(255, 85, 85, 85));
	}
}

// Draws square tile at given pixel position
void	draw_tile(t_app *app, t_int_p pixel, u_int32_t trgb)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (++y < TILE_SIZE - 1)
	{
		x = 0;
		while (++x < TILE_SIZE - 1)
			my_mlx_pixel_put(app->screen->img, x + pixel.x, y + pixel.y, trgb);
	}
	// printf("\na\n");
}

// Returns given tile's color
u_int32_t	pick_color(char map_tile)
{
	u_int32_t	color;

	if (map_tile == WALL)
		color = create_trgb(255, 0, 0, 0);			// Wall			(black)
	else if (map_tile == DOOR)
		color = create_trgb(255, 255, 0, 255);		// Door			(purple)
	else if (map_tile == TORCH)
		color = create_trgb(255, 255, 255, 0);		// Enemy		(red)
	else
		color = create_trgb(255, 255, 255, 255);	// Empty tile	(white)
	return (color);
}

void	draw_map(t_app *app)
{
	t_map		*map;
	size_t		tile_y;
	size_t		tile_x;
	t_int_p		pixel;
	u_int32_t	color;

	map = app->game->map;
	tile_y = -1;
	while (++tile_y < map->max_height && tile_y < app->screen->height / 6)
	{
		tile_x = -1;
		while (++tile_x < map->max_width  && tile_x < app->screen->width / 6)
		{
			color = pick_color(map->map_arr[tile_y][tile_x]);
			pixel.x = tile_x * TILE_SIZE + 4;
			pixel.y = tile_y * TILE_SIZE + 4;
			draw_tile(app, pixel, color);
		}
	}
}

// Draws line from pixel begin to end
void	draw_facing_ray(t_app *app, t_float_p begin, t_float_p end)
{
	u_int32_t	color;
	double		dx;
	double		dy;

	end.x = begin.x + end.x * 5;
	end.y = begin.y + end.y * 5;
	color = create_trgb(255, 0, 0, 255);
	// To get the direction of the line in 2D space, you can end - begin
	dx = end.x - begin.x; // 10
	dy = end.y - begin.y; // 0

	// From this, we can approximate the number of pixels we’ll have to draw along the way.
	int			pixels = sqrt(pow(dx, 2) + pow(dy, 2));
	// pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10

	// The reason why we used double was so we can divide the total distance of our line by the amount of pixels we’ll have to draw.
	dx /= pixels; // 1
	dy /= pixels; // 0

	// So we can finally start plotting the line with a very simple loop
	double		pixel_x = begin.x;
	double		pixel_y = begin.y;
	while (pixels)
	{
		my_mlx_pixel_put(app->screen->img, pixel_x, pixel_y, color);
		// mlx_pixel_put(mlx, win, pixel_x, pixel_y, color);
		pixel_x += dx;
		pixel_y += dy;
		--pixels;
	}
}

void	draw_torches(t_app *app)
{
	size_t	i;
	t_int_p	pixel;

	if (app->game->torches)
	{
		i = -1;
		while (++i < app->game->n_torches)
		{
			pixel.x = app->game->torches[i].pos.x;
			pixel.y = app->game->torches[i].pos.y;
			draw_circle(app->screen->img, pixel, create_trgb(255, 255, 255, 0));
		}
	}
}

// void	draw_player(t_app *app)
// {
// 	t_entity	player;
// 	t_int_p		pixel;
// 	player = app->game->player;
// 	pixel.x = player.pos.x;
// 	pixel.y = player.pos.y;
// 	draw_circle(app->screen->img, pixel, create_trgb(255, 0, 0, 255));
// 	draw_facing_ray(app, player.pos, player.delta);
// }

// void	draw_entities(t_app *app)
// {
// 	draw_player(app);
// 	// draw_torches(app);
// }

void	draw_player(int x, int y, t_screen *s)
{

	draw_circle2(s->img, s->width - x * MINIMAP_TILE_SIZE +
		MINIMAP_TILE_SIZE / 2, y * MINIMAP_TILE_SIZE
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
	int	j;
	int	i;
	u_int32_t	c;

	i = -1;
	while (++i < (int)game->map->max_width)
	{
		j = 0;
		while (++j <= (int)game->map->max_height)
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
	// draw_2d_background(app);
	// draw_map(app);
	// draw_entities(app);
	// my_mlx_put_image_to_window(app);
}
