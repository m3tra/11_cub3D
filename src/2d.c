/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:30:46 by fporto            #+#    #+#             */
/*   Updated: 2023/03/14 19:57:50 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Paints entire screen as gray
void	draw_2d_background(t_app *app)
{
	t_screen	*screen;
	size_t		x;
	size_t		y;

	screen = app->screen;
	y = -1;
	while (++y < screen->height)
	{
		x = -1;
		while (++x < screen->width)
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
	while (++tile_y < map->max_height)
	{
		tile_x = -1;
		while (++tile_x < map->max_width)
		{
			color = pick_color(map->map_arr[tile_y][tile_x]);
			pixel.x = tile_x * TILE_SIZE;
			pixel.y = tile_y * TILE_SIZE;
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
	color = create_trgb(255, 0, 255, 0);
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

void	draw_player(t_app *app)
{
	t_entity	player;
	t_int_p		pixel;

	player = app->game->player;
	pixel.x = player.pos.x;
	pixel.y = player.pos.y;

	draw_circle(app->screen->img, pixel, create_trgb(255, 0, 0, 255));
	draw_facing_ray(app, player.pos, player.delta);
}

void	draw_entities(t_app *app)
{
	draw_player(app);
	draw_torches(app);
}

int	draw2d(t_app *app)
{
	draw_2d_background(app);
	draw_map(app);
	draw_entities(app);
	my_mlx_put_image_to_window(app);
	// printf("facing: %f\n", app->game->player.facing / M_PI);
	// printf("delta->x: %f\n", app->game->player.delta.x);
	// printf("delta->y: %f\n", app->game->player.delta.y);
	return (1);
}
